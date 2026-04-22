#include <fstream>
#include <stdint.h>

// Referencing the variables defined in GameEngine.cpp
extern float HEALTH;
extern float SANITY;
extern float BATTERY;

void executeBinarySave(const char* path) {
    std::ofstream file(path, std::ios::binary | std::ios::out);
    if (file.is_open()) {
        file.write(reinterpret_cast<char*>(&HEALTH), sizeof(float));
        file.write(reinterpret_cast<char*>(&SANITY), sizeof(float));
        file.write(reinterpret_cast<char*>(&BATTERY), sizeof(float));
        file.close();
    }
}

void executeBinaryLoad(const char* path) {
    std::ifstream file(path, std::ios::binary | std::ios::in);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&HEALTH), sizeof(float));
        file.read(reinterpret_cast<char*>(&SANITY), sizeof(float));
        file.read(reinterpret_cast<char*>(&BATTERY), sizeof(float));
        file.close();
    }
}
