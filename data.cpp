#include <stdint.h>
#include <math.h>

extern "C" {
    // Survival Stats
    float PLAYER_HEALTH = 100.0f;
    bool IS_DEAD = false;

    // Proximity variables from previous update
    float PLAYER_X = 0.0f, PLAYER_Y = 0.0f, PLAYER_Z = 0.0f;
    float ENTITY_X = 0.0f, ENTITY_Y = 0.0f, ENTITY_Z = 0.0f;

    void processDamage() {
        if (IS_DEAD) return;

        float dx = PLAYER_X - ENTITY_X;
        float dy = PLAYER_Y - ENTITY_Y;
        float dz = PLAYER_Z - ENTITY_Z;
        float distance = sqrt(dx*dx + dy*dy + dz*dz);

        // If entity is within 1.5 units, take damage
        if (distance < 1.5f) {
            PLAYER_HEALTH -= 1.5f; // Rapid drain
        }

        if (PLAYER_HEALTH <= 0) {
            PLAYER_HEALTH = 0;
            IS_DEAD = true;
        }
    }

    bool checkDeathState() {
        return IS_DEAD;
    }
}
