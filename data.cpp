#include <jni.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

extern "C" {
    float P_X = 0.0f, P_Z = 0.0f, E_X = 5.0f, E_Z = 5.0f;
    float HEALTH = 100.0f, STAMINA = 100.0f, BATTERY = 100.0f, SANITY = 100.0f;
    float CAMERA_PITCH = 0.0f, CAMERA_YAW = 0.0f;
    bool IS_DEAD = false;
    bool NIGHT_VISION_ACTIVE = false;

    // JNI Mapping: java.graphics.PlayerEngine.checkDeathStatus()
    JNIEXPORT jboolean JNICALL Java_java_graphics_PlayerEngine_checkDeathStatus(JNIEnv* env, jclass clazz) {
        return IS_DEAD;
    }

    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processTick(JNIEnv* env, jclass clazz, jboolean sprinting, jboolean lightOn) {
        if (IS_DEAD) {
            // Freeze movement and camera jitter on death
            return;
        }

        // --- Survival Drains ---
        if (NIGHT_VISION_ACTIVE && BATTERY > 0) BATTERY -= 0.25f;
        else if (lightOn && BATTERY > 0) BATTERY -= 0.08f;
        else if (BATTERY < 100.0f) BATTERY += 0.04f;

        if (!lightOn && !NIGHT_VISION_ACTIVE) SANITY -= 0.02f;

        // --- Glitch (0 Sanity) ---
        if (SANITY <= 0.0f) {
            SANITY = 0.0f;
            P_X += ((rand() % 10 - 5) * 0.01f);
            CAMERA_YAW += ((rand() % 10 - 5) * 0.05f);
        }

        // --- Collision & Death Trigger ---
        float dx = P_X - E_X, dz = P_Z - E_Z;
        if (fabsf(dx) < 1.2f && fabsf(dz) < 1.2f) {
            HEALTH -= 10.0f; // Higher damage for final build
            if (HEALTH <= 0) {
                HEALTH = 0;
                IS_DEAD = true;
            }
        }
    }
}
