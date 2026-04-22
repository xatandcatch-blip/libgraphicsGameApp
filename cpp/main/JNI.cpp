#include <jni.h>

extern int GRAPHICS_QUALITY;

extern "C" {
    JNIEXPORT void JNICALL Java_java_graphics_PlayerEngine_setGraphicsQuality(JNIEnv* env, jclass clazz, jint quality) {
        if (quality >= 0 && quality <= 2) {
            GRAPHICS_QUALITY = quality;
        }
    }

    JNIEXPORT jint JNICALL Java_java_graphics_PlayerEngine_getGraphicsQuality(JNIEnv* env, jclass clazz) {
        return GRAPHICS_QUALITY;
    }
}
