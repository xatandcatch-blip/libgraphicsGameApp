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

// 1. Define Collision First
bool isWallAt(float x, float z) {
    if (x > 4.8f || x < -4.8f || z > 4.8f || z < -4.8f) {
        return true;
    }
    return false;
}

// 2. Define Line of Sight (Now it knows what isWallAt is)
bool hasLineOfSight(float ex, float ez, float px, float pz) {
    float midX = (ex + px) / 2.0f;
    float midZ = (ez + pz) / 2.0f;
    return !isWallAt(midX, midZ); 
}

float calculateDistance(float x1, float z1, float x2, float z2) {
    return sqrt(pow(x2 - x1, 2) + pow(z2 - z1, 2));
}

// 3. Game Logic Bridge
void processGameLoop(JNIEnv* env) {
    float dist = calculateDistance(P_X, P_Z, E_X, E_Z);

    jclass logicClass = env->FindClass("java/main/GameLogic");
    if (logicClass) {
        jmethodID getRate = env->GetStaticMethodID(logicClass, "getHeartbeatRate", "(F)F");
        float rate = env->CallStaticFloatMethod(logicClass, getRate, dist);
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

void updateFlashlight(JNIEnv* env, float distToEntity) {
    jclass logicClass = env->FindClass("java/main/GameLogic");
    if (logicClass) {
        jmethodID getDrain = env->GetStaticMethodID(logicClass, "getBatteryDrainRate", "(F)F");
        float drainAmount = env->CallStaticFloatMethod(logicClass, getDrain, distToEntity);
        
        // Apply the drain to the global battery
        BATTERY -= drainAmount;
        
        if (BATTERY < 0.0f) {
            BATTERY = 0.0f;
            // Trigger: Flashlight dies, player is in total darkness
        }
    }
}

void checkSawRoomTrigger(JNIEnv* env) {
    // If player is inside the "Saw Room" coordinates (e.g., center of the hall)
    if (P_X > -1.0f && P_X < 1.0f && P_Z > -1.0f && P_Z < 1.0f) {
        // Force hiding to false via JNI
        jclass logicClass = env->FindClass("java/main/GameLogic");
        jmethodID setHiding = env->GetStaticMethodID(logicClass, "setHidingState", "(Z)V");
        env->CallStaticVoidMethod(logicClass, setHiding, false);
        
        // Maybe drop sanity rapidly
        SANITY -= 0.5f;
    }
}
