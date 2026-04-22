#include <math.h>

float HEALTH = 100.0f, SANITY = 100.0f, BATTERY = 100.0f;
float P_X = 0.0f, P_Z = 0.0f;
int SODA_COUNT = 0, SPARE_BATTERIES = 0, DEATH_COUNT = 0;

// Flashlight Logic: Only drains if active
void updateBattery(bool isOn, bool isSprinting) {
    if (!isOn) return; // 0% drain if light is off

    float drainRate = 0.05f; // Base drain
    if (isSprinting) {
        drainRate = 0.12f; // High drain while running
    }

    BATTERY -= drainRate;
    if (BATTERY < 0.0f) BATTERY = 0.0f;
}

void runEngineTick() {
    if (SANITY < 0.0f) SANITY = 0.0f;
}
