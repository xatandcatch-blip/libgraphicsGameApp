#include <stdint.h>
#include <math.h>

extern "C" {
    // Core Coordinates & Rotation
    float P_X = 0.0f, P_Y = 0.0f, P_Z = 0.0f;
    float E_X = 5.0f, E_Y = 0.0f, E_Z = 5.0f;
    float CAMERA_YAW = 0.0f;
    float CAMERA_PITCH = 0.0f;
    
    // Stats
    float PLAYER_HEALTH = 100.0f;
    float STAMINA = 100.0f;
    float BATTERY = 100.0f;
    bool IS_DEAD = false;

    // Physics Constants
    float HITBOX_SIZE = 1.2f;
    float KNOCKBACK_STRENGTH = 2.5f;
    float RECOIL_STRENGTH = 0.15f; // Screen jerk amount

    bool isHitboxTrigger() {
        float dx = fabsf(P_X - E_X);
        float dz = fabsf(P_Z - E_Z);
        return (dx < HITBOX_SIZE && dz < HITBOX_SIZE);
    }

    void applyKnockbackAndRecoil() {
        float dx = P_X - E_X;
        float dz = P_Z - E_Z;
        float distance = sqrtf(dx * dx + dz * dz);

        if (distance > 0.0f) {
            // Position Push
            P_X += (dx / distance) * KNOCKBACK_STRENGTH;
            P_Z += (dz / distance) * KNOCKBACK_STRENGTH;

            // Camera Recoil (Jerk the view upward and slightly random left/right)
            CAMERA_PITCH -= RECOIL_STRENGTH; 
            CAMERA_YAW += (RECOIL_STRENGTH * 0.5f); 
        }
    }

    void updateNativeTick(bool isSprinting, bool flashlightOn) {
        if (isSprinting && STAMINA > 0) STAMINA -= 0.5f;
        else if (STAMINA < 100.0f) STAMINA += 0.2f;

        if (flashlightOn && BATTERY > 0) BATTERY -= 0.08f;
        else if (!flashlightOn && BATTERY < 100.0f) BATTERY += 0.04f;

        if (isHitboxTrigger()) {
            PLAYER_HEALTH -= 5.0f;
            applyKnockbackAndRecoil();
            if (PLAYER_HEALTH <= 0) IS_DEAD = true;
        }
    }
}
