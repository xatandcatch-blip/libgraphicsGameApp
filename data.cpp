#include <stdint.h>
#include <math.h>

extern "C" {
    // --- Global State ---
    float P_X = 0.0f, P_Z = 0.0f;
    float E_X = 5.0f, E_Z = 5.0f;
    float HEALTH = 100.0f, STAMINA = 100.0f, BATTERY = 100.0f, SANITY = 100.0f;
    float CAMERA_PITCH = 0.0f;
    bool IS_HIDING = false, IS_DEAD = false;

    // --- Collision Logic (com.logic.CollisionLogic) ---
    bool Java_com_logic_CollisionLogic_isHitboxTrigger(void* env, jclass clazz) {
        float dx = fabsf(P_X - E_X);
        float dz = fabsf(P_Z - E_Z);
        return (dx < 1.2f && dz < 1.2f);
    }

    // --- Engine Logic (com.logic.EngineLogic) ---
    void Java_com_logic_EngineLogic_updateNativeTick(void* env, jclass clazz, bool isSprinting, bool lightOn) {
        if (IS_DEAD) return;

        // 1. Survival Drains
        if (isSprinting && STAMINA > 0) STAMINA -= 0.5f;
        else if (STAMINA < 100.0f) STAMINA += 0.2f;

        if (lightOn && BATTERY > 0) BATTERY -= 0.08f;
        else if (!lightOn && BATTERY < 100.0f) BATTERY += 0.04f;

        // 2. Sanity & Hiding
        if (IS_HIDING) {
            if (SANITY < 100.0f) SANITY += 0.05f;
        } else {
            if (!lightOn) SANITY -= 0.02f;
        }

        // 3. Hit Response
        if (Java_com_logic_CollisionLogic_isHitboxTrigger(env, clazz)) {
            HEALTH -= 5.0f;
            // Knockback Math
            float dx = P_X - E_X;
            float dz = P_Z - E_Z;
            float dist = sqrtf(dx*dx + dz*dz);
            if (dist > 0) {
                P_X += (dx/dist) * 2.5f;
                P_Z += (dz/dist) * 2.5f;
                CAMERA_PITCH -= 0.15f; // Recoil
            }
        }

        if (HEALTH <= 0) IS_DEAD = true;
        
        // 4. Camera Recovery
        if (CAMERA_PITCH < 0.0f) CAMERA_PITCH += 0.02f;
    }

    float Java_com_logic_EngineLogic_getSanityWarp(void* env, jclass clazz) {
        return 1.0f - (SANITY / 100.0f);
    }

    // --- Anti-Cheat (com.logic.AntiCheat) ---
    bool Java_com_logic_AntiCheat_checkIntegrity(void* env, jclass clazz) {
        return (HEALTH <= 100.0f && STAMINA <= 100.0f); // Basic value clamp check
    }
}
