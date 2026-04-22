#include <jni.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

extern "C" {
    // --- Global State Variables ---
    float P_X = 0.0f, P_Y = 0.0f, P_Z = 0.0f;
    float E_X = 5.0f, E_Y = 0.0f, E_Z = 5.0f;
    float HEALTH = 100.0f, STAMINA = 100.0f, BATTERY = 100.0f, SANITY = 100.0f;
    float CAMERA_PITCH = 0.0f, CAMERA_YAW = 0.0f;
    float ENTITY_SPEED = 0.05f;
    
    bool IS_HIDING = false, IS_DEAD = false, IS_FLICKERING = false;

    // --- Internal Math Helpers ---
    bool checkHitbox() {
        float dx = fabsf(P_X - E_X);
        float dz = fabsf(P_Z - E_Z);
        return (dx < 1.2f && dz < 1.2f);
    }

    // --- java.graphics.PlayerEngine Mapping ---
    JNIEXPORT jboolean JNICALL Java_java_graphics_PlayerEngine_isColliding(JNIEnv* env, jclass clazz) {
        return checkHitbox();
    }

    // --- java.main.Smali.PlayerEngineStartLogic Mapping ---
    JNIEXPORT jint JNICALL Java_java_main_Smali_PlayerEngineStartLogic_getHeartbeatIntensity(JNIEnv* env, jclass clazz) {
        float dx = P_X - E_X;
        float dz = P_Z - E_Z;
        float dist = sqrtf(dx*dx + dz*dz);
        if (dist > 10.0f) return 0;
        return (jint)((1.0f - (dist / 10.0f)) * 100.0f);
    }

    // --- java.main.Smali.EngineStartLogic Mapping (The Main Tick) ---
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processTick(JNIEnv* env, jclass clazz, jboolean sprinting, jboolean lightOn) {
        if (IS_DEAD) return;

        // 1. Movement & Survival Drains
        if (sprinting && STAMINA > 0) STAMINA -= 0.5f;
        else if (STAMINA < 100.0f) STAMINA += 0.2f;

        if (lightOn && BATTERY > 0) {
            BATTERY -= 0.08f;
            if (BATTERY < 15.0f) IS_FLICKERING = (rand() % 10 == 0);
        } else if (BATTERY < 100.0f) {
            BATTERY += 0.04f;
        }

        // 2. Sanity Logic
        if (IS_HIDING) {
            if (SANITY < 100.0f) SANITY += 0.05f;
        } else {
            if (!lightOn) SANITY -= 0.02f;
            if (checkHitbox()) SANITY -= 0.1f;
        }

        // 3. Collision, Knockback & Recoil
        if (checkHitbox()) {
            HEALTH -= 5.0f;
            float dx = P_X - E_X, dz = P_Z - E_Z;
            float dist = sqrtf(dx*dx + dz*dz);
            if (dist > 0) {
                P_X += (dx/dist) * 2.5f; // Knockback
                P_Z += (dz/dist) * 2.5f;
                CAMERA_PITCH -= 0.15f;    // Recoil
            }
            if (HEALTH <= 0) IS_DEAD = true;
        }

        // 4. Recovery & AI Scaling
        if (CAMERA_PITCH < 0.0f) CAMERA_PITCH += 0.02f;
        float sanityLoss = 1.0f - (SANITY / 100.0f);
        ENTITY_SPEED = 0.05f + (0.05f * sanityLoss);
    }
}
