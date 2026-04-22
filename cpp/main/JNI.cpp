#include <jni.h>

extern int DEATH_COUNT;
extern void applyDeathPenalty();

extern "C" {
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_handlePlayerDeath(JNIEnv* env, jclass clazz) {
        DEATH_COUNT++;
        applyDeathPenalty();
        // The Smali layer will then call saveGame() to lock in the penalty
    }
}
