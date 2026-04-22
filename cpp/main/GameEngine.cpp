#include <jni.h>
#include <math.h>
#include <stdlib.h>
#include <string>

// Global Stats
float HEALTH = 100.0f, SANITY = 100.0f, BATTERY = 100.0f;
float P_X = 0.0f, P_Z = 0.0f;
float E_X = 10.0f, E_Z = 10.0f; 
int SODA_COUNT = 0, SPARE_BATTERIES = 0, DEATH_COUNT = 0;
int GRAPHICS_QUALITY = 1; 
float MASTER_VOLUME = 0.8f;

// Logic to check distance to Entity
float calculateDistance(float x1, float z1, float x2, float z2) {
    return sqrt(pow(x2 - x1, 2) + pow(z2 - z1, 2));
}

// THE BRIDGE: Talking to GameLogic.java
void processGameLoop(JNIEnv* env) {
    float dist = calculateDistance(P_X, P_Z, E_X, E_Z);

    jclass logicClass = env->FindClass("java/main/GameLogic");
    if (logicClass) {
        jmethodID getRate = env->GetStaticMethodID(logicClass, "getHeartbeatRate", "(F)F");
        float rate = env->CallStaticFloatMethod(logicClass, getRate, dist);
        // 'rate' now holds the value from your Java code!
    }
}

void applyDeathPenalty() {
    DEATH_COUNT++;
    if (SODA_COUNT > 2) SODA_COUNT -= 1;
    HEALTH = (HEALTH < 40.0f) ? 40.0f : 50.0f;
    SANITY = 70.0f; 
}

void runEngineTick() {
    if (SANITY < 0.0f) SANITY = 0.0f;
}
