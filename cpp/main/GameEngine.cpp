#include <math.h>

float HEALTH = 100.0f, SANITY = 100.0f, BATTERY = 100.0f;
float P_X = 0.0f, P_Z = 0.0f;
int SODA_COUNT = 0;
int SPARE_BATTERIES = 0;

// Persistent Death Counter
int DEATH_COUNT = 0;

void runEngineTick() {
    if (SANITY < 0.0f) SANITY = 0.0f;
}
