#include <stdint.h>

extern "C" {
    // Survival Database
    int32_t PLAYER_HEALTH = 100;
    
    // NPC AI Entity Data
    bool ENTITY_SPAWNED = false;
    float ENTITY_POS_Z = 0.0f;

    // Touch Input & Camera Data
    float TOUCH_X = 0.0f;
    float TOUCH_Y = 0.0f;
    float CAMERA_YAW = 0.0f;   // Left/Right rotation
    float CAMERA_PITCH = 0.0f; // Up/Down rotation

    // Update camera based on delta touch movement
    void handleTouchInput(float x, float y) {
        float deltaX = x - TOUCH_X;
        float deltaY = y - TOUCH_Y;
        
        CAMERA_YAW += deltaX * 0.01f;
        CAMERA_PITCH += deltaY * 0.01f;
        
        TOUCH_X = x;
        TOUCH_Y = y;
    }

    void spawnMansionEntity(float x, float y, float z) {
        ENTITY_SPAWNED = true;
        ENTITY_POS_Z = z;
    }
}
