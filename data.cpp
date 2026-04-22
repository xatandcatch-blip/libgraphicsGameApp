#include <stdint.h>

extern "C" {
    // Survival Stats
    int32_t PLAYER_HEALTH = 100;
    
    // NPC AI Entity Data
    bool ENTITY_SPAWNED = false;
    float ENTITY_POS_X = 0.0f;
    float ENTITY_POS_Y = 0.0f;
    float ENTITY_POS_Z = 0.0f;

    // Spawn Logic: Moves entity to starting point in the Mansion
    void spawnMansionEntity(float x, float y, float z) {
        ENTITY_POS_X = x;
        ENTITY_POS_Y = y;
        ENTITY_POS_Z = z;
        ENTITY_SPAWNED = true;
    }

    // Existing AI Update
    void updateAI() {
        if (ENTITY_SPAWNED) {
            ENTITY_POS_Z += 0.1f; // Slow drift toward player
        }
    }
}
