#include <jni.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

extern "C" {
    // Stats & State
    float P_X = 0.0f, P_Z = 0.0f, E_X = 5.0f, E_Z = 5.0f;
    float HEALTH = 100.0f, STAMINA = 100.0f, BATTERY = 100.0f, SANITY = 100.0f;
    float CAMERA_PITCH = 0.0f, CAMERA_YAW = 0.0f;
    bool IS_DEAD = false, IS_FLICKERING = false;

    // Helper: Reset glitching when drinking
    void resetSanityState() {
        SANITY = 100.0f;
        // Optional: Add a small health or stamina boost from the sugar
        if (STAMINA < 100.0f) STAMINA += 20.0f;
    }

    // JNI Mapping: java.graphics.PlayerEngine.drinkSoda()
    JNIEXPORT void JNICALL Java_java_graphics_PlayerEngine_drinkSoda(JNIEnv* env, jclass clazz) {
        resetSanityState();
    }

    // JNI Mapping: java.main.Smali.EngineStartLogic.processTick
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processTick(JNIEnv* env, jclass clazz, jboolean sprinting, jboolean lightOn) {
        if (IS_DEAD) return;

        // Survival Drains
        if (sprinting && STAMINA > 0) STAMINA -= 0.5f;
        else if (STAMINA < 100.0f) STAMINA += 0.2f;

        if (lightOn && BATTERY > 0) {
            BATTERY -= 0.08f;
            if (BATTERY < 15.0f) IS_FLICKERING = (rand() % 10 == 0);
        } else if (BATTERY < 100.0f) BATTERY += 0.04f;

        // Sanity Drain & Glitch
        if (!lightOn) SANITY -= 0.02f;
        
        if (SANITY <= 0.0f) {
            SANITY = 0.0f;
            P_X += ((rand() % 10 - 5) * 0.01f);
            P_Z += ((rand() % 10 - 5) * 0.01f);
            CAMERA_YAW += ((rand() % 10 - 5) * 0.05f);
        }

        // Standard Collision & Health
        float dx = P_X - E_X, dz = P_Z - E_Z;
        if (fabsf(dx) < 1.2f && fabsf(dz) < 1.2f) {
            HEALTH -= 5.0f;
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
