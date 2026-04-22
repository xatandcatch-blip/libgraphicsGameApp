#include <jni.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

extern "C" {
    // Stats & Engine State
    float P_X = 0.0f, P_Y = 0.0f, P_Z = 0.0f;
    float E_X = 5.0f, E_Y = 0.0f, E_Z = 5.0f;
    float HEALTH = 100.0f, STAMINA = 100.0f, BATTERY = 100.0f, SANITY = 100.0f;
    float CAMERA_PITCH = 0.0f, CAMERA_YAW = 0.0f;
    bool IS_DEAD = false, IS_FLICKERING = false;

    // Internal Math: Collision Check
    bool checkHitbox() {
        float dx = fabsf(P_X - E_X);
        float dz = fabsf(P_Z - E_Z);
        return (dx < 1.2f && dz < 1.2f);
    }

    // New: Glitch Logic for 0% Sanity
    void applySanityGlitch() {
        if (SANITY <= 0.0f) {
            // High-speed jitter: Perturb position by small random amounts
            P_X += ((rand() % 10 - 5) * 0.01f);
            P_Z += ((rand() % 10 - 5) * 0.01f);
            CAMERA_YAW += ((rand() % 10 - 5) * 0.05f);
        }
    }

    // JNI Mapping: java.main.Smali.PlayerEngineStartLogic
    JNIEXPORT jint JNICALL Java_java_main_Smali_PlayerEngineStartLogic_getHeartbeatIntensity(JNIEnv* env, jclass clazz) {
        float dx = P_X - E_X, dz = P_Z - E_Z;
        float dist = sqrtf(dx*dx + dz*dz);
        if (dist > 10.0f) return 0;
        return (jint)((1.0f - (dist / 10.0f)) * 100.0f);
    }

    // JNI Mapping: java.main.Smali.EngineStartLogic.processTick
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processTick(JNIEnv* env, jclass clazz, jboolean sprinting, jboolean lightOn) {
        if (IS_DEAD) return;

        // 1. Survival & Drains
        if (sprinting && STAMINA > 0) STAMINA -= 0.5f;
        else if (STAMINA < 100.0f) STAMINA += 0.2f;

        if (lightOn && BATTERY > 0) {
            BATTERY -= 0.08f;
            if (BATTERY < 15.0f) IS_FLICKERING = (rand() % 10 == 0);
        } else if (BATTERY < 100.0f) BATTERY += 0.04f;

        // 2. Sanity & Glitch Application
        if (!lightOn) SANITY -= 0.02f;
        applySanityGlitch(); // Apply jitter if SANITY is 0

        // 3. Collision, Knockback & Recoil
        if (checkHitbox()) {
            HEALTH -= 5.0f;
            float dx = P_X - E_X, dz = P_Z - E_Z;
            float dist = sqrtf(dx*dx + dz*dz);
            if (dist > 0) {
                P_X += (dx/dist) * 2.5f;
                P_Z += (dz/dist) * 2.5f;
                CAMERA_PITCH -= 0.15f;
            }
        }

        if (HEALTH <= 0) IS_DEAD = true;
        if (CAMERA_PITCH < 0.0f) CAMERA_PITCH += 0.02f;
    }
}
