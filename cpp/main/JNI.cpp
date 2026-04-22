#include <jni.h>

extern float MASTER_VOLUME;

extern "C" {
    JNIEXPORT void JNICALL Java_java_graphics_PlayerEngine_setVolume(JNIEnv* env, jclass clazz, jfloat volume) {
        if (volume >= 0.0f && volume <= 1.0f) {
            MASTER_VOLUME = volume;
        }
    }

    JNIEXPORT jfloat JNICALL Java_java_graphics_PlayerEngine_getVolume(JNIEnv* env, jclass clazz) {
        return MASTER_VOLUME;
    }
}
