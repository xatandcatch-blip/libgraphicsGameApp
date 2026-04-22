#include <jni.h>
#include <math.h>
#include <stdlib.h>
#include <string>

// Global Stats & State
float HEALTH = 100.0f, SANITY = 100.0f, BATTERY = 100.0f;
float P_X = 0.0f, P_Z = 0.0f;
float E_X = 10.0f, E_Z = 10.0f; 
bool SAW_ROOM_LOCKED = false;

enum EntityState { IDLE, WANDERING, CHASING, SEARCHING };
EntityState currentAIState = IDLE;

float calculateDistance(float x1, float z1, float x2, float z2) {
    return sqrt(pow(x2 - x1, 2) + pow(z2 - z1, 2));
}

bool hasLineOfSight(float ex, float ez, float px, float pz) {
    // Raycast midpoint check
    float midX = (ex + px) / 2.0f;
    float midZ = (ez + pz) / 2.0f;
    return (midX < 4.8f && midX > -4.8f && midZ < 4.8f && midZ > -4.8f);
}

void processAI(JNIEnv* env) {
    float dist = calculateDistance(P_X, P_Z, E_X, E_Z);
    bool los = hasLineOfSight(E_X, E_Z, P_X, P_Z);

    // AI State Transitions
    if (currentAIState == IDLE && dist < 12.0f) currentAIState = WANDERING;
    if (los && dist < 8.0f) currentAIState = CHASING;
    if (currentAIState == CHASING && !los) currentAIState = SEARCHING;
    
    // Logic for Chase Speed
    if (currentAIState == CHASING) {
        E_X += (P_X > E_X) ? 0.05f : -0.05f;
        E_Z += (P_Z > E_Z) ? 0.05f : -0.05f;
    }
}
