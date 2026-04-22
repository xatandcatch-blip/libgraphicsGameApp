#include <stdint.h>

extern "C" {
    // Core Engine Stats
    int32_t PLAYER_HEALTH = 100;
    int32_t PLAYER_LEVEL = 36;
    
    // Domain Expansion: Infinite Void Logic
    bool DOMAIN_ACTIVE = false;
    float DOMAIN_RADIUS = 50.0f;
    int32_t DOMAIN_SURE_HIT_DAMAGE = 9999;

    // Trigger Function for Vulkan Core
    void triggerDomain() {
        DOMAIN_ACTIVE = true;
    }
}
