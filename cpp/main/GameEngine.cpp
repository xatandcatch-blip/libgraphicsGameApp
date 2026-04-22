#include <math.h>

// Master definitions of the engine variables
float HEALTH = 100.0f;
float SANITY = 100.0f;
float BATTERY = 100.0f;
float P_X = 0.0f;
float P_Z = 0.0f;

// Inventory tracking
int SODA_COUNT = 0;
int SPARE_BATTERIES = 0;

void runEngineTick() {
    // Basic survival logic: Sanity cannot drop below zero
    if (SANITY < 0.0f) {
        SANITY = 0.0f;
    }
    
    // You can add logic here to drain battery over time
    // or reduce sanity in the dark later.
}
