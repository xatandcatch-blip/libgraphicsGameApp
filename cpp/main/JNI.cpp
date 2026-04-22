#include <jni.h>

extern void runEngineTick();
extern int SODA_COUNT;
extern int SPARE_BATTERIES;

extern "C" {
    // Standard Tick
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processTick(JNIEnv* env, jclass clazz) {
        runEngineTick();
    }

    // New: Item Pickup Handler
    // type 0 = Soda, type 1 = Battery
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_pickupItem(JNIEnv* env, jclass clazz, jint type) {
        if (type == 0) {
            SODA_COUNT++;
        } else if (type == 1) {
            SPARE_BATTERIES++;
        }
    }
}
