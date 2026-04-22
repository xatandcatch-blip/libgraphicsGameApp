#include <jni.h>

extern void runEngineTick();
extern void updateBattery(bool isOn, bool isSprinting);
extern bool useBatteryItem();

extern "C" {
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processTick(JNIEnv* env, jclass clazz, jboolean lightOn, jboolean sprinting) {
        runEngineTick();
        updateBattery((bool)lightOn, (bool)sprinting);
    }

    // Returns true if a battery was used
    JNIEXPORT jboolean JNICALL Java_java_main_Smali_EngineStartLogic_replaceBattery(JNIEnv* env, jclass clazz) {
        return (jboolean)useBatteryItem();
    }
}
