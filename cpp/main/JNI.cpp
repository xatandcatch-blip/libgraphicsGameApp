#include <jni.h>

extern void runEngineTick();

extern "C" {
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processTick(JNIEnv* env, jclass clazz) {
        runEngineTick();
    }
}
