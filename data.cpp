#include <jni.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

extern "C" {
    // Player & Entity Stats
    float P_X = 0.0f, P_Z = 0.0f, E_X = 10.0f, E_Z = 10.0f;
    float HEALTH = 100.0f, SANITY = 100.0f, BATTERY = 100.0f;
    bool IS_DEAD = false;

    // World & AI Logic
    int CURRENT_CHUNK = 0;
    float NOISE_LEVEL = 0.0f;
    float BASE_AI_SPEED = 0.04f;

    // Helper: Seed-based World Generation
    JNIEXPORT jint JNICALL Java_java_main_Smali_EngineStartLogic_generateChunk(JNIEnv* env, jclass clazz, jint seed) {
        srand(seed + CURRENT_CHUNK);
        CURRENT_CHUNK++;
        return (rand() % 4); // Returns a room type: 0=Hall, 1=Room, 2=Closet, 3=Trap
    }

    // Main Tick: Integrated Noise Detection
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processTick(JNIEnv* env, jclass clazz, jboolean sprinting, jboolean lightOn) {
        if (IS_DEAD) return;

        // 1. Noise Calculation
        if (sprinting) {
            NOISE_LEVEL = 1.5f; // Sprints are loud
        } else {
            NOISE_LEVEL = 0.2f; // Crouching/Walking is quiet
        }

        // 2. AI Hearing Logic
        float dx = P_X - E_X, dz = P_Z - E_Z;
        float dist = sqrtf(dx*dx + dz*dz);

        if (dist < (5.0f * NOISE_LEVEL)) {
            // Entity "Hears" you and moves toward P_X, P_Z faster
            E_X += (dx / dist) * (BASE_AI_SPEED * 1.5f);
            E_Z += (dz / dist) * (BASE_AI_SPEED * 1.5f);
        } else {
            // Patrol/Idle speed
            E_X += 0.01f; 
        }

        // 3. Collision & Survival Logic
        if (dist < 1.2f) {
            HEALTH -= 10.0f;
            if (HEALTH <= 0) IS_DEAD = true;
        }

        // 4. Sanity & Battery
        if (!lightOn) SANITY -= 0.02f;
        if (lightOn) BATTERY -= 0.08f;
    }
}
