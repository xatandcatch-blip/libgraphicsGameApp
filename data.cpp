#include <stdint.h>
#include <math.h>
#include <stdlib.h> // For rand()

extern "C" {
    // Stats
    float BATTERY = 100.0f;
    bool FLASHLIGHT_ON = false;
    bool IS_FLICKERING = false;

    // Environmental Logic: Updates frame-by-frame
    void updateEnvironment() {
        if (FLASHLIGHT_ON) {
            BATTERY -= 0.08f;
            
            // Flicker logic: If under 15%, 1 in 10 chance to flicker
            if (BATTERY < 15.0f) {
                IS_FLICKERING = (rand() % 10 == 0); 
            } else {
                IS_FLICKERING = false;
            }

            if (BATTERY <= 0) {
                BATTERY = 0;
                FLASHLIGHT_ON = false;
                IS_FLICKERING = false;
            }
        } else if (BATTERY < 100.0f) {
            BATTERY += 0.04f; // Recharge
            IS_FLICKERING = false;
        }
    }

    // This is the value the Fragment Shader actually uses
    float getLightIntensity() {
        if (!FLASHLIGHT_ON) return 0.0f;
        if (IS_FLICKERING) return 0.2f; // Dim flick
        return 1.0f; // Full bright
    }
}
