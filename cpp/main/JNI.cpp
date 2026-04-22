#include <jni.h>

extern void runEngineTick();
extern void processGameLoop(JNIEnv* env);

extern "C" {
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processTick(JNIEnv* env, jclass clazz) {
        runEngineTick();
        processGameLoop(env);
    }

    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_setHiding(JNIEnv* env, jclass clazz, jboolean hiding) {
        jclass logicClass = env->FindClass("java/main/GameLogic");
        jmethodID setHiding = env->GetStaticMethodID(logicClass, "setHidingState", "(Z)V");
        env->CallStaticVoidMethod(logicClass, setHiding, hiding);
    }
}
