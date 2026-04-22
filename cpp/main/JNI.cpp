#include <jni.h>

extern void runEngineTick();
extern int DEATH_COUNT;

extern "C" {
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processTick(JNIEnv* env, jclass clazz) {
        runEngineTick();
    }

    // Called when the death screen is triggered
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_incrementDeath(JNIEnv* env, jclass clazz) {
        DEATH_COUNT++;
    }
}
