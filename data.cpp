#include <jni.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

extern "C" {
    // Master State
    float P_X = 0.0f, P_Z = 0.0f, E_X = 10.0f, E_Z = 10.0f;
    float HEALTH = 100.0f, SANITY = 100.0f, BATTERY = 100.0f;
    bool IS_DEAD = false;

    // --- Audio Logic: Heartbeat Pulse ---
    JNIEXPORT jfloat JNICALL Java_java_graphics_PlayerEngine_getHeartbeatRate(JNIEnv* env, jclass clazz) {
        float dx = P_X - E_X, dz = P_Z - E_Z;
        float dist = sqrtf(dx*dx + dz*dz);
        
        if (dist > 15.0f) return 0.0f; // Silence
        // Returns a frequency multiplier (1.0 to 3.0)
        return 1.0f + (2.0f * (1.0f - (dist / 15.0f)));
    }

    // --- World Gen Logic ---
    JNIEXPORT jint JNICALL Java_java_main_Smali_EngineStartLogic_generateChunk(JNIEnv* env, jclass clazz, jint seed) {
        static int chunk_count = 0;
        srand(seed + chunk_count++);
        return (rand() % 4); 
    }

    // --- Main Survival & AI Tick ---
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processTick(JNIEnv* env, jclass clazz, jboolean sprinting, jboolean lightOn) {
        if (IS_DEAD) return;

        float noise = sprinting ? 2.0f : 0.3f;
        float dx = P_X - E_X, dz = P_Z - E_Z;
        float dist = sqrtf(dx*dx + dz*dz);

        // AI "Hearing" movement
        if (dist < (8.0f * noise)) {
            E_X += (dx / dist) * 0.06f;
            E_Z += (dz / dist) * 0.06f;
        }

        // Survival Mechanics
        if (lightOn) BATTERY -= 0.08f;
        if (!lightOn) SANITY -= 0.02f;
        
        if (dist < 1.2f) {
            HEALTH -= 10.0f;
            if (HEALTH <= 0) IS_DEAD = true;
        }
    }
}
