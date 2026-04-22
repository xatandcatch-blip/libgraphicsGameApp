#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <string>
#include <vector>

extern "C" {
    // We pass the AssetManager from Java/Smali to C++
    JNIEXPORT void JNICALL Java_java_graphics_PlayerEngine_initAssetManager(JNIEnv* env, jclass clazz, jobject assetManager) {
        AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
        // Now 'mgr' can be used to open mansion_hall.obj
    }

    // Helper to read text files (like our .obj or .sfd)
    std::string loadTextAsset(AAssetManager* mgr, const char* filename) {
        AAsset* asset = AAssetManager_open(mgr, filename, AASSET_MODE_BUFFER);
        if (!asset) return "";

        size_t size = AAsset_getLength(asset);
        std::vector<char> buffer(size);
        AAsset_read(asset, buffer.data(), size);
        AAsset_close(asset);

        return std::string(buffer.begin(), buffer.end());
    }
}
