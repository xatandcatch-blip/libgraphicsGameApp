#include <math.h>

float HEALTH = 100.0f, SANITY = 100.0f, BATTERY = 100.0f;
float P_X = 0.0f, P_Z = 0.0f;

void runEngineTick() {
    // Math for AI and survival goes here
    if (SANITY < 0) SANITY = 0;
}
