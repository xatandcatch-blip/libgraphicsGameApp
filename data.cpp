#include <jni.h>
#include <fstream>
#include <stdint.h>
#include <algorithm> // For std::clamp

extern "C" {
    // Game State
    float HEALTH = 100.0f, STAMINA = 100.0f, BATTERY = 100.0f, SANITY = 100.0f;
    float P_X = 0.0f, P_Z = 0.0f;

    // Hard Clamp Function: The "Guardian" of the memory
    void applySafetyClamps() {
        HEALTH = std::clamp(HEALTH, 0.0f, 100.0f);
        STAMINA = std::clamp(STAMINA, 0.0f, 100.0f);
        BATTERY = std::clamp(BATTERY, 0.0f, 100.0f);
        SANITY = std::clamp(SANITY, 0.0f, 100.0f);
    }

    // JNI Mapped: Process Tick with Safety
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processTick(JNIEnv* env, jclass clazz, jboolean sprinting, jboolean lightOn) {
        // ... (rest of your movement and AI logic)

        // Run safety check at the end of every frame
        applySafetyClamps();
    }

    // Binary Save/Load (Native .rune)
    JNIEXPORT void JNICALL Java_java_graphics_PlayerEngine_saveGame(JNIEnv* env, jclass clazz, jstring path) {
        applySafetyClamps(); // Secure data before saving
        const char* nativePath = env->GetStringUTFChars(path, 0);
        std::ofstream file(nativePath, std::ios::binary);
        if (file.is_open()) {
            file.write(reinterpret_cast<char*>(&HEALTH), sizeof(float) * 4); // Save H/S/B/S block
            file.close();
        }
        env->ReleaseStringUTFChars(path, nativePath);
    }
}
