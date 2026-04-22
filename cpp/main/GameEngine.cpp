#include <math.h>
#include <stdlib.h>

float HEALTH = 100.0f, SANITY = 100.0f, BATTERY = 100.0f;
float P_X = 0.0f, P_Z = 0.0f, E_X = 15.0f, E_Z = 15.0f;
int SODA_COUNT = 0, SPARE_BATTERIES = 0, DEATH_COUNT = 0;

// Hallucination Shake Offsets
float SHAKE_X = 0.0f, SHAKE_Z = 0.0f;

void runEngineTick() {
    if (SANITY < 0.0f) SANITY = 0.0f;

    // Hallucination Logic: Shake intensity increases as sanity drops below 40%
    if (SANITY < 40.0f) {
        float intensity = (40.0f - SANITY) * 0.01f;
        SHAKE_X = ((rand() % 100) / 100.0f - 0.5f) * intensity;
        SHAKE_Z = ((rand() % 100) / 100.0f - 0.5f) * intensity;
    } else {
        SHAKE_X = 0.0f;
        SHAKE_Z = 0.0f;
    }
}

// Check if entity is close enough for a jump-scare
bool checkScareTrigger() {
    float dx = P_X - E_X;
    float dz = P_Z - E_Z;
    float dist = sqrtf(dx*dx + dz*dz);
    
    // Trigger if within 2 meters and not already dead
    return (dist < 2.0f && HEALTH > 0);
}

void updateBattery(bool isOn, bool isSprinting) {
    if (!isOn) return;
    BATTERY -= isSprinting ? 0.12f : 0.05f;
    if (BATTERY < 0.0f) BATTERY = 0.0f;
}

bool useBatteryItem() {
    if (SPARE_BATTERIES > 0 && BATTERY < 90.0f) {
        SPARE_BATTERIES--;
        BATTERY = 100.0f;
        return true;
    }
    return false;
}
