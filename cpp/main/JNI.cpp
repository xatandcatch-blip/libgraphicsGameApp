#include <jni.h>

extern void applyDeathPenalty();

extern "C" {
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_handlePlayerDeath(JNIEnv* env, jclass clazz) {
        applyDeathPenalty();
        // The core logic is now self-balancing to prevent "Death Loops"
    }
}
