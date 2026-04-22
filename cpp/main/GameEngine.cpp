#include <math.h>

float HEALTH = 100.0f, SANITY = 100.0f, BATTERY = 100.0f;
float P_X = 0.0f, P_Z = 0.0f;
int SODA_COUNT = 0, SPARE_BATTERIES = 0, DEATH_COUNT = 0;

void updateBattery(bool isOn, bool isSprinting) {
    if (!isOn) return; 

    float drainRate = 0.05f; 
    if (isSprinting) drainRate = 0.12f; 

    BATTERY -= drainRate;
    if (BATTERY < 0.0f) BATTERY = 0.0f;
}

// Logic to swap a spare for a full charge
bool useBatteryItem() {
    if (SPARE_BATTERIES > 0 && BATTERY < 90.0f) {
        SPARE_BATTERIES--;
        BATTERY = 100.0f;
        return true; // Success
    }
    return false; // No spares or battery already full
}

void runEngineTick() {
    if (SANITY < 0.0f) SANITY = 0.0f;
}
