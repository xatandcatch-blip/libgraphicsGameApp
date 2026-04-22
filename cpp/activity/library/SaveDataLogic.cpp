#include <fstream>
#include <stdint.h>

extern float HEALTH, SANITY, BATTERY; // Link to data.cpp globals

void executeBinarySave(const char* path) {
    std::ofstream file(path, std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<char*>(&HEALTH), sizeof(float));
        file.write(reinterpret_cast<char*>(&SANITY), sizeof(float));
        file.write(reinterpret_cast<char*>(&BATTERY), sizeof(float));
        file.close();
    }
}
