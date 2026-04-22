#include <math.h>
#include <stdlib.h>

float HEALTH = 100.0f, SANITY = 100.0f, BATTERY = 100.0f;
float P_X = 0.0f, P_Z = 0.0f;
int SODA_COUNT = 0, SPARE_BATTERIES = 0, DEATH_COUNT = 0;
int GRAPHICS_QUALITY = 1; 
float MASTER_VOLUME = 0.8f;

void applyDeathPenalty() {
    // Increment total deaths regardless
    DEATH_COUNT++;

    // MERCY LOGIC: Only tax sodas if they have more than 2
    if (SODA_COUNT > 2) {
        SODA_COUNT -= 1; // Just a small tax, not half
    }

    // MERCY LOGIC: Don't set health lower than 40% 
    // This ensures they always have a fighting chance to escape
    if (HEALTH < 40.0f) {
        HEALTH = 40.0f; 
    } else {
        HEALTH = 50.0f;
    }

    // Reset Sanity to a manageable level so the screen stops shaking
    SANITY = 70.0f; 
}

void runEngineTick() {
    if (SANITY < 0.0f) SANITY = 0.0f;
}
