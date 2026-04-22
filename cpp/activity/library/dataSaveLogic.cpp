#include <jni.h>

extern void executeBinarySave(const char* path);
extern bool executeBinaryLoad(const char* path);

extern "C" {
    JNIEXPORT jboolean JNICALL Java_java_graphics_PlayerEngine_loadGame(JNIEnv* env, jclass clazz, jstring path) {
        const char* nativePath = env->GetStringUTFChars(path, 0);
        bool success = executeBinaryLoad(nativePath);
        env->ReleaseStringUTFChars(path, nativePath);
        return (jboolean)success;
    }
}
