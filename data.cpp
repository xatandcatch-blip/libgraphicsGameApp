#include <jni.h>
#include <fstream>
#include <stdint.h>

extern "C" {
    // Data Structure for the .rune format
    struct SaveData {
        float px, py, pz;
        float health, stamina, battery, sanity;
        int current_chunk;
    };

    // External stats (restored)
    float P_X = 0.0f, P_Y = 0.0f, P_Z = 0.0f;
    float HEALTH = 100.0f, STAMINA = 100.0f, BATTERY = 100.0f, SANITY = 100.0f;
    int CURRENT_CHUNK = 0;

    // JNI Mapping: java.graphics.PlayerEngine.saveGame(String path)
    JNIEXPORT void JNICALL Java_java_graphics_PlayerEngine_saveGame(JNIEnv* env, jclass clazz, jstring path) {
        const char* nativePath = env->GetStringUTFChars(path, 0);
        
        SaveData data = {P_X, 0.0f, P_Z, HEALTH, STAMINA, BATTERY, SANITY, CURRENT_CHUNK};
        
        std::ofstream file(nativePath, std::ios::binary);
        if (file.is_open()) {
            file.write(reinterpret_cast<char*>(&data), sizeof(SaveData));
            file.close();
        }
        
        env->ReleaseStringUTFChars(path, nativePath);
    }

    // JNI Mapping: java.graphics.PlayerEngine.loadGame(String path)
    JNIEXPORT void JNICALL Java_java_graphics_PlayerEngine_loadGame(JNIEnv* env, jclass clazz, jstring path) {
        const char* nativePath = env->GetStringUTFChars(path, 0);
        
        SaveData data;
        std::ifstream file(nativePath, std::ios::binary);
        if (file.is_open()) {
            file.read(reinterpret_cast<char*>(&data), sizeof(SaveData));
            
            // Restore state
            P_X = data.px; P_Z = data.pz;
            HEALTH = data.health; STAMINA = data.stamina;
            BATTERY = data.battery; SANITY = data.sanity;
            CURRENT_CHUNK = data.current_chunk;
            
            file.close();
        }
        
        env->ReleaseStringUTFChars(path, nativePath);
    }
}
