#include <stdint.h>
#include <math.h>

extern "C" {
    // Player State
    float SANITY = 100.0f;
    bool IS_HIDING = false;
    bool FLASHLIGHT_ON = false;
    
    // AI Control
    float ENTITY_SPEED = 0.05f;
    float BASE_SPEED = 0.05f;

    // Toggle Hiding (called when entering a hiding spot)
    void setHiding(bool hiding) {
        IS_HIDING = hiding;
        if (IS_HIDING) {
            FLASHLIGHT_ON = false; // Auto-off flashlight when hiding
        }
    }

    void updateStealthLogic(bool isNearEntity) {
        if (IS_HIDING) {
            // Sanity recovers slightly while hiding in the dark
            if (SANITY < 100.0f) SANITY += 0.01f;
            ENTITY_SPEED = 0.0f; // Entity "stops" or loses player
            return;
        }

        // Standard Drain
        if (!FLASHLIGHT_ON) SANITY -= 0.02f;
        if (isNearEntity) SANITY -= 0.05f;

        // Apply Speed Scaling based on Sanity
        float sanityLoss = 1.0f - (SANITY / 100.0f);
        ENTITY_SPEED = BASE_SPEED + (BASE_SPEED * sanityLoss);
    }
}
