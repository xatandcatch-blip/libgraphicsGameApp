#include <stdint.h>
#include <math.h>

extern "C" {
    // Player & Entity Stats
    float P_X = 0.0f, P_Y = 0.0f, P_Z = 0.0f;
    float E_X = 5.0f, E_Y = 0.0f, E_Z = 5.0f;
    float PLAYER_HEALTH = 100.0f;
    float STAMINA = 100.0f;
    float BATTERY = 100.0f;
    
    // Hitbox Constants
    float HITBOX_SIZE = 1.2f;
    bool IS_DEAD = false;

    // The "Brain": Math for the Smali Trigger
    bool isHitboxTrigger() {
        float dx = fabsf(P_X - E_X);
        float dz = fabsf(P_Z - E_Z);
        // Returns true if boxes overlap
        return (dx < HITBOX_SIZE && dz < HITBOX_SIZE);
    }

    // Process frame-by-frame environmental logic
    void updateNativeTick(bool isSprinting, bool flashlightOn) {
        // Stamina Logic
        if (isSprinting && STAMINA > 0) STAMINA -= 0.5f;
        else if (STAMINA < 100.0f) STAMINA += 0.2f;

        // Battery Logic
        if (flashlightOn && BATTERY > 0) BATTERY -= 0.08f;
        else if (!flashlightOn && BATTERY < 100.0f) BATTERY += 0.04f;

        // Death Check
        if (isHitboxTrigger()) {
            PLAYER_HEALTH -= 1.0f;
            if (PLAYER_HEALTH <= 0) IS_DEAD = true;
        }
    }
}
