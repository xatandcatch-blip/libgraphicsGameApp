#include <stdint.h>

extern "C" {
    // Survival Database
    int32_t PLAYER_HEALTH = 100;
    int32_t PLAYER_STAMINA = 100;
    
    // NPC AI Entity States
    // 0 = Idle, 1 = Searching, 2 = Chasing
    int32_t ENTITY_STATE = 0; 
    float ENTITY_X = 0.0f;
    float ENTITY_Y = 0.0f;
    float ENTITY_SPEED = 3.2f;

    // Native AI Logic
    void updateAI() {
        if (PLAYER_HEALTH > 0) {
            ENTITY_STATE = 2; // Set to Chase mode
        }
    }
}
