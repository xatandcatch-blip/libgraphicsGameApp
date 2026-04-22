#include <stdint.h>
#include <math.h>

extern "C" {
    // Survival Stats
    float PLAYER_X = 0.0f, PLAYER_Y = 0.0f, PLAYER_Z = 0.0f;
    float ENTITY_X = 10.0f, ENTITY_Y = 0.0f, ENTITY_Z = 10.0f;
    
    float HEARTBEAT_INTENSITY = 0.0f; // 0.0 (Calm) to 1.0 (Panic)

    // Calculate how close the horror is
    void updateHeartbeat() {
        float dx = PLAYER_X - ENTITY_X;
        float dy = PLAYER_Y - ENTITY_Y;
        float dz = PLAYER_Z - ENTITY_Z;
        
        float distance = sqrt(dx*dx + dy*dy + dz*dz);

        // Intensity starts at 15 units away, maxes at 2 units
        if (distance < 15.0f) {
            HEARTBEAT_INTENSITY = 1.0f - ((distance - 2.0f) / 13.0f);
            if (HEARTBEAT_INTENSITY > 1.0f) HEARTBEAT_INTENSITY = 1.0f;
            if (HEARTBEAT_INTENSITY < 0.0f) HEARTBEAT_INTENSITY = 0.0f;
        } else {
            HEARTBEAT_INTENSITY = 0.0f;
        }
    }

    // Keep existing battery/stamina logic in the compiled core...
}
