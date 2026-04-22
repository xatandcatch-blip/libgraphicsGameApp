#include <jni.h>
#include <stdint.h>
#include <math.h>
#include <algorithm>

extern "C" {
    // Player & Entity positions
    float P_X = 0.0f, P_Z = 0.0f;
    float E_X = 10.0f, E_Z = 10.0f;
    float E_ROT = 0.0f; // Entity rotation
    
    // Simple Collision Map (0 = Empty, 1 = Wall)
    // In a real build, this would be populated by generateChunk()
    int MANSION_MAP[10][10] = {0}; 

    // Helper: Check if a coordinate is a wall
    bool isWall(float x, float z) {
        int ix = (int)roundf(x);
        int iz = (int)roundf(z);
        if (ix < 0 || ix >= 10 || iz < 0 || iz >= 10) return true;
        return MANSION_MAP[ix][iz] == 1;
    }

    // JNI Mapping: AI Pathfinding Tick
    JNIEXPORT void JNICALL Java_java_main_Smali_EngineStartLogic_processAiPath(JNIEnv* env, jclass clazz) {
        float dx = P_X - E_X;
        float dz = P_Z - E_Z;
        float targetRot = atan2f(dz, dx);

        // Ray-casting: Check if the direct path is blocked
        float checkX = E_X + cosf(targetRot) * 1.5f;
        float checkZ = E_Z + sinf(sinf(targetRot)) * 1.5f;

        if (isWall(checkX, checkZ)) {
            // Obstacle detected! Veer Left/Right to find an opening
            E_ROT += 0.5f; 
        } else {
            // Path clear! Smoothly rotate toward player
            E_ROT += (targetRot - E_ROT) * 0.1f;
        }

        // Move the entity based on final rotation
        E_X += cosf(E_ROT) * 0.04f;
        E_Z += sinf(E_ROT) * 0.04f;
    }
}
