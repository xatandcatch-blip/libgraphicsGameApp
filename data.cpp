#include <stdint.h>
#include <math.h>
#include <stdlib.h>

extern "C" {
    // Stats & Meters
    float BATTERY = 100.0f;
    float SANITY = 100.0f;
    bool FLASHLIGHT_ON = false;
    
    // AI Constants
    float ENTITY_SPEED = 0.05f;
    float BASE_SPEED = 0.05f;

    void updateSanity(bool isNearEntity) {
        // Drain sanity if light is off or entity is close
        if (!FLASHLIGHT_ON) {
            SANITY -= 0.02f;
        }
        if (isNearEntity) {
            SANITY -= 0.05f;
        }

        // Clamp sanity
        if (SANITY < 0.0f) SANITY = 0.0f;
        if (SANITY > 100.0f) SANITY = 100.0f;

        // Scale Entity Speed: As sanity drops, entity gets up to 2x faster
        float sanityLoss = 1.0f - (SANITY / 100.0f);
        ENTITY_SPEED = BASE_SPEED + (BASE_SPEED * sanityLoss);
    }

    float getSanityWarp() {
        // Returns a value for the shader to distort the screen
        return 1.0f - (SANITY / 100.0f);
    }
}
