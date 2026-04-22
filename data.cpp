#include <stdint.h>

extern "C" {
    // Survival Stats
    int32_t PLAYER_HEALTH = 100;
    float PLAYER_STAMINA = 100.0f;
    float MAX_STAMINA = 100.0f;
    
    // Sprinting Logic
    bool IS_SPRINTING = false;
    float SPRINT_DRAIN = 0.5f;
    float REGEN_RATE = 0.2f;

    void setSprinting(bool sprinting) {
        IS_SPRINTING = sprinting;
    }

    // Processed every frame by the engine
    void updateSurvivalStats() {
        if (IS_SPRINTING && PLAYER_STAMINA > 0) {
            PLAYER_STAMINA -= SPRINT_DRAIN;
        } else if (!IS_SPRINTING && PLAYER_STAMINA < MAX_STAMINA) {
            PLAYER_STAMINA += REGEN_RATE;
        }

        // Force stop sprint if exhausted
        if (PLAYER_STAMINA <= 0) {
            IS_SPRINTING = false;
        }
    }

    // Previous logic remains
    void handleTouchInput(float x, float y) { /* Camera logic */ }
}
