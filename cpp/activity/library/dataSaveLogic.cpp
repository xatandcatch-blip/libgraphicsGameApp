#include <jni.h>

extern void executeBinarySave(const char* path);
extern void executeBinaryLoad(const char* path);

extern "C" {
    JNIEXPORT void JNICALL Java_java_graphics_PlayerEngine_saveGame(JNIEnv* env, jclass clazz, jstring path) {
        const char* nativePath = env->GetStringUTFChars(path, 0);
        executeBinarySave(nativePath); // Fixed: Call Save here
        env->ReleaseStringUTFChars(path, nativePath);
    }

    JNIEXPORT void JNICALL Java_java_graphics_PlayerEngine_loadGame(JNIEnv* env, jclass clazz, jstring path) {
        const char* nativePath = env->GetStringUTFChars(path, 0);
        executeBinaryLoad(nativePath); // Correct: Call Load here
        env->ReleaseStringUTFChars(path, nativePath);
    }
}

extern bool checkSaveExists(const char* path);

extern "C" {
    JNIEXPORT jboolean JNICALL Java_java_graphics_PlayerEngine_hasSaveFile(JNIEnv* env, jclass clazz, jstring path) {
        const char* nativePath = env->GetStringUTFChars(path, 0);
        bool exists = checkSaveExists(nativePath);
        env->ReleaseStringUTFChars(path, nativePath);
        return (jboolean)exists;
    }
}

extern bool executeDeleteSave(const char* path);

extern "C" {
    JNIEXPORT jboolean JNICALL Java_java_graphics_PlayerEngine_deleteSaveFile(JNIEnv* env, jclass clazz, jstring path) {
        const char* nativePath = env->GetStringUTFChars(path, 0);
        bool deleted = executeDeleteSave(nativePath);
        env->ReleaseStringUTFChars(path, nativePath);
        return (jboolean)deleted;
    }
}
