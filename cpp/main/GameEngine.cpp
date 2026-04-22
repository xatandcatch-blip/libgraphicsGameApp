#include <math.h>
#include <stdlib.h>

float HEALTH = 100.0f, SANITY = 100.0f, BATTERY = 100.0f;
float P_X = 0.0f, P_Z = 0.0f;
int SODA_COUNT = 0, SPARE_BATTERIES = 0, DEATH_COUNT = 0;

// Graphics Quality: 0: Low, 1: Medium, 2: High
int GRAPHICS_QUALITY = 1; 

void runEngineTick() {
    if (SANITY < 0.0f) SANITY = 0.0f;
}
