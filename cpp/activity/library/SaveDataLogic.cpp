#include <fstream>
#include <stdint.h>

extern float HEALTH, SANITY, BATTERY;
extern int SODA_COUNT, SPARE_BATTERIES, DEATH_COUNT;

void executeBinarySave(const char* path) {
    std::ofstream file(path, std::ios::binary | std::ios::out);
    if (file.is_open()) {
        file.write(reinterpret_cast<char*>(&HEALTH), sizeof(float));
        file.write(reinterpret_cast<char*>(&SANITY), sizeof(float));
        file.write(reinterpret_cast<char*>(&BATTERY), sizeof(float));
        file.write(reinterpret_cast<char*>(&SODA_COUNT), sizeof(int));
        file.write(reinterpret_cast<char*>(&SPARE_BATTERIES), sizeof(int));
        file.write(reinterpret_cast<char*>(&DEATH_COUNT), sizeof(int));
        file.close();
    }
}

void executeBinaryLoad(const char* path) {
    std::ifstream file(path, std::ios::binary | std::ios::in);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&HEALTH), sizeof(float));
        file.read(reinterpret_cast<char*>(&SANITY), sizeof(float));
        file.read(reinterpret_cast<char*>(&BATTERY), sizeof(float));
        file.read(reinterpret_cast<char*>(&SODA_COUNT), sizeof(int));
        file.read(reinterpret_cast<char*>(&SPARE_BATTERIES), sizeof(int));
        file.read(reinterpret_cast<char*>(&DEATH_COUNT), sizeof(int));
        file.close();
    }
}
