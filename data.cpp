#include <stdint.h>
#include <math.h>

extern "C" {
    // Core Coordinates
    float P_X = 0.0f, P_Y = 0.0f, P_Z = 0.0f;
    float E_X = 5.0f, E_Y = 0.0f, E_Z = 5.0f;
    
    // Stats & State
    float PLAYER_HEALTH = 100.0f;
    float STAMINA = 100.0f;
    float BATTERY = 100.0f;
    bool IS_DEAD = false;

    // Hitbox & Physics Constants
    float HITBOX_SIZE = 1.2f;
    float KNOCKBACK_STRENGTH = 2.5f;

    // The Smali-Linked Trigger
    bool isHitboxTrigger() {
        float dx = fabsf(P_X - E_X);
        float dz = fabsf(P_Z - E_Z);
        return (dx < HITBOX_SIZE && dz < HITBOX_SIZE);
    }

    // Physical Response Logic
    void applyKnockback() {
        float dx = P_X - E_X;
        float dz = P_Z - E_Z;
        float distance = sqrtf(dx * dx + dz * dz);

        if (distance > 0.0f) {
            // Push player in the opposite direction of the entity
            P_X += (dx / distance) * KNOCKBACK_STRENGTH;
            P_Z += (dz / distance) * KNOCKBACK_STRENGTH;
        }
    }

    void updateNativeTick(bool isSprinting, bool flashlightOn) {
        // Environmental drain/regen
        if (isSprinting && STAMINA > 0) STAMINA -= 0.5f;
        else if (STAMINA < 100.0f) STAMINA += 0.2f;

        if (flashlightOn && BATTERY > 0) BATTERY -= 0.08f;
        else if (!flashlightOn && BATTERY < 100.0f) BATTERY += 0.04f;

        // Collision & Physics processing
        if (isHitboxTrigger()) {
            PLAYER_HEALTH -= 5.0f;
            applyKnockback();
            if (PLAYER_HEALTH <= 0) IS_DEAD = true;
        }
    }
}
