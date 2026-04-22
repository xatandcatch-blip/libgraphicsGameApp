#include <math.h>
#include <stdlib.h>
#include <string>

float HEALTH = 100.0f, SANITY = 100.0f, BATTERY = 100.0f;
float P_X = 0.0f, P_Z = 0.0f;
int SODA_COUNT = 0, SPARE_BATTERIES = 0, DEATH_COUNT = 0;
int GRAPHICS_QUALITY = 1; 
float MASTER_VOLUME = 0.8f;

// Logic to "play" a sound from assets/sounds/
void triggerAmbientSound(const char* soundName) {
    // In a real OpenSL ES or Oboe implementation, 
    // you would multiply the raw buffer by MASTER_VOLUME here.
    float finalVolume = MASTER_VOLUME; 
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

// Simple AABB (Axis-Aligned Bounding Box) for walls
bool isWallAt(float x, float z) {
    // Basic boundary for the mansion hall (-5 to 5)
    if (x > 4.8f || x < -4.8f || z > 4.8f || z < -4.8f) {
        return true;
    }
    return false;
}

void updateEntityAI(float& ex, float& ez, float px, float pz) {
    float moveSpeed = 0.02f;
    
    // Move toward player X
    float nextX = (ex < px) ? ex + moveSpeed : ex - moveSpeed;
    if (!isWallAt(nextX, ez)) ex = nextX;

    // Move toward player Z
    float nextZ = (ez < pz) ? ez + moveSpeed : ez - moveSpeed;
    if (!isWallAt(ex, nextZ)) ez = nextZ;
}

// Mock Entity Position
float E_X = 10.0f, E_Z = 10.0f;

float calculateDistance(float x1, float z1, float x2, float z2) {
    return sqrt(pow(x2 - x1, 2) + pow(z2 - z1, 2));
}

void processGameLoop(JNIEnv* env) {
    float dist = calculateDistance(P_X, P_Z, E_X, E_Z);

    // Call Java GameLogic to get heartbeat rate
    jclass logicClass = env->FindClass("java/main/GameLogic");
    jmethodID getRate = env->GetStaticMethodID(logicClass, "getHeartbeatRate", "(F)F");
    float rate = env->CallStaticFloatMethod(logicClass, getRate, dist);

    // If the rate is high (player is close), we can trigger a camera shake or sound
    if (rate > 3.0f) {
        // PANIC MODE
    }
}
