#include <jni.h>
#include <fstream>
#include <stdint.h>
#include <math.h>

extern "C" {
    float P_X = 0.0f, P_Z = 0.0f;
    float HEALTH = 100.0f, SANITY = 100.0f, BATTERY = 100.0f;
    bool IS_HIDING = false;

    // JNI: Toggle Hiding and Auto-Save
    JNIEXPORT void JNICALL Java_java_graphics_PlayerEngine_setHiding(JNIEnv* env, jclass clazz, jboolean hiding, jstring savePath) {
        IS_HIDING = hiding;
        
        // Auto-save to .rune when entering a closet
        if (IS_HIDING) {
            const char* path = env->GetStringUTFChars(savePath, 0);
            std::ofstream file(path, std::ios::binary);
            if (file.is_open()) {
                file.write(reinterpret_cast<char*>(&HEALTH), sizeof(float));
                file.write(reinterpret_cast<char*>(&SANITY), sizeof(float));
                file.close();
            }
            env->ReleaseStringUTFChars(savePath, path);
        }
    }

    // AI Pathing now respects hiding
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processAiPath(JNIEnv* env, jclass clazz) {
        if (IS_HIDING) return; // AI loses track of you
        // ... (Pathfinding math here)
    }
}
