#include <stdint.h>

extern "C" {
    // Player Survival Stats
    int32_t PLAYER_HEALTH = 100;
    int32_t PLAYER_STAMINA = 100;
    
    // Saw Room Engine Variables
    bool TRAP_ACTIVE = false;
    float SAW_SPEED = 5.5f;
    int32_t ROOM_LIGHT_INTENSITY = 10; // Dark for Horror

    // Native Function to trigger room events
    void activateSawTrap() {
        TRAP_ACTIVE = true;
    }
}
