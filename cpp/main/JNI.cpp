#include <jni.h>

extern void runEngineTick();

extern "C" {
    // Call this from the UI when the "Crouch" button is held
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_setHiding(JNIEnv* env, jclass clazz, jboolean hiding) {
        jclass logicClass = env->FindClass("java/main/GameLogic");
        jmethodID setHiding = env->GetStaticMethodID(logicClass, "setHidingState", "(Z)V");
        env->CallStaticVoidMethod(logicClass, setHiding, hiding);
    }

    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processTick(JNIEnv* env, jclass clazz, jboolean lightOn, jboolean sprinting) {
        runEngineTick();
    }
}
