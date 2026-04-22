#include <stdint.h>

extern "C" {
    // Survival Stats
    int32_t PLAYER_HEALTH = 100;
    float PLAYER_STAMINA = 100.0f;
    
    // Flashlight & Battery System
    bool FLASHLIGHT_ON = false;
    float BATTERY_LEVEL = 100.0f;
    float MAX_BATTERY = 100.0f;
    float BATTERY_DRAIN_RATE = 0.08f;
    float RECHARGE_RATE = 0.04f; // Slower than the drain

    void toggleFlashlight() {
        if (BATTERY_LEVEL > 10.0f || FLASHLIGHT_ON) { 
            // Requires 10% charge to turn back on
            FLASHLIGHT_ON = !FLASHLIGHT_ON;
        }
    }

    // Native tick for the environment
    void updateEnvironment() {
        if (FLASHLIGHT_ON) {
            BATTERY_LEVEL -= BATTERY_DRAIN_RATE;
            if (BATTERY_LEVEL <= 0) {
                BATTERY_LEVEL = 0;
                FLASHLIGHT_ON = false;
            }
        } else if (!FLASHLIGHT_ON && BATTERY_LEVEL < MAX_BATTERY) {
            BATTERY_LEVEL += RECHARGE_RATE;
        }
    }
}
