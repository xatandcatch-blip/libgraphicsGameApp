#include <jni.h>

extern void runEngineTick();
extern bool checkScareTrigger();
extern float SHAKE_X, SHAKE_Z;

extern "C" {
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processTick(JNIEnv* env, jclass clazz, jboolean lightOn, jboolean sprinting) {
        runEngineTick();
        // Update battery logic (handled in GameEngine)
    }

    // Returns a jump-scare signal
    JNIEXPORT jboolean JNICALL Java_java_main_Smali_EngineStartLogic_shouldScare(JNIEnv* env, jclass clazz) {
        return (jboolean)checkScareTrigger();
    }

    // Get Native Hallucination Offsets for the Camera
    JNIEXPORT jfloat JNICALL Java_java_main_Smali_EngineStartLogic_getShakeX(JNIEnv* env, jclass clazz) { return SHAKE_X; }
    JNIEXPORT jfloat JNICALL Java_java_main_Smali_EngineStartLogic_getShakeZ(JNIEnv* env, jclass clazz) { return SHAKE_Z; }
}
