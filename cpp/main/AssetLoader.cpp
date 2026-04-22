#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <string>
#include <vector>

// Internal C++ Helper (NO extern "C" here)
std::string loadTextAsset(AAssetManager* mgr, const char* filename) {
    AAsset* asset = AAssetManager_open(mgr, filename, AASSET_MODE_BUFFER);
    if (!asset) return "";

    size_t size = AAsset_getLength(asset);
    std::vector<char> buffer(size);
    AAsset_read(asset, buffer.data(), size);
    AAsset_close(asset);

    return std::string(buffer.begin(), buffer.end());
}

// JNI Interface (Requires extern "C")
extern "C" {
    JNIEXPORT void JNICALL Java_java_graphics_PlayerEngine_initAssetManager(JNIEnv* env, jclass clazz, jobject assetManager) {
        AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
        // We'll store this pointer globally in a real implementation
    }
}
