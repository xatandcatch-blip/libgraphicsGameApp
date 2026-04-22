#include <jni.h>

extern void executeBinarySave(const char* path);

extern "C" {
    JNIEXPORT void JNICALL Java_java_graphics_PlayerEngine_saveGame(JNIEnv* env, jclass clazz, jstring path) {
        const char* nativePath = env->GetStringUTFChars(path, 0);
        executeBinarySave(nativePath);
        env->ReleaseStringUTFChars(path, nativePath);
    }
}
