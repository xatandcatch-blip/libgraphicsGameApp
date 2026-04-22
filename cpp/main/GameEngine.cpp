#include <math.h>
#include <stdlib.h>

float HEALTH = 100.0f, SANITY = 100.0f, BATTERY = 100.0f;
float P_X = 0.0f, P_Z = 0.0f;
int SODA_COUNT = 0, SPARE_BATTERIES = 0, DEATH_COUNT = 0;
int GRAPHICS_QUALITY = 1; 
float MASTER_VOLUME = 0.8f;

// The Penalty: Losing resources instead of the whole save
void applyDeathPenalty() {
    HEALTH = 50.0f;     // Start weak
    SANITY = 60.0f;     // Start panicked
    SODA_COUNT /= 2;    // Lose half your drinks as a "tax"
}

void runEngineTick() {
    if (SANITY < 0.0f) SANITY = 0.0f;
}
