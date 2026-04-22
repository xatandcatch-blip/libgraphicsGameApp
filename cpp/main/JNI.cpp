#include <jni.h>

extern void runEngineTick();
extern void updateBattery(bool isOn, bool isSprinting);

extern "C" {
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processTick(JNIEnv* env, jclass clazz, jboolean lightOn, jboolean sprinting) {
        // Run survival logic
        runEngineTick();
        
        // Handle battery consumption
        updateBattery((bool)lightOn, (bool)sprinting);
    }

    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_incrementDeath(JNIEnv* env, jclass clazz) {
        extern int DEATH_COUNT;
        DEATH_COUNT++;
    }
}
