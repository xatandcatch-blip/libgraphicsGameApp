#include <jni.h>
#include <stdint.h>
#include <math.h>

extern "C" {
    float P_X = 0.0f, P_Z = 0.0f, E_X = 5.0f, E_Z = 5.0f;
    float HEALTH = 100.0f, SANITY = 100.0f;
    
    // Returns 0-100 based on proximity for haptic feedback
    JNIEXPORT jint JNICALL Java_java_main_Smali_PlayerEngineStartLogic_getHeartbeatIntensity(JNIEnv* env, jclass clazz) {
        float dx = P_X - E_X;
        float dz = P_Z - E_Z;
        float dist = sqrtf(dx*dx + dz*dz);
        
        if (dist > 10.0f) return 0; // Too far
        if (dist < 1.5f) return 100; // Maximum panic
        
        // Linear scale: closer = higher intensity
        return (jint)((1.0f - (dist / 10.0f)) * 100.0f);
    }

    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processTick(JNIEnv* env, jclass clazz, jboolean sprinting, jboolean lightOn) {
        // ... (Previous logic for health, stamina, and movement remains here)
    }
}
