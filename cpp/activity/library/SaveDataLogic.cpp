#include <fstream>
#include <stdint.h>

extern float HEALTH, SANITY, BATTERY, MASTER_VOLUME;
extern int SODA_COUNT, SPARE_BATTERIES, DEATH_COUNT, GRAPHICS_QUALITY;

void executeBinarySave(const char* path) {
    std::ofstream file(path, std::ios::binary | std::ios::out);
    if (file.is_open()) {
        file.write(reinterpret_cast<char*>(&HEALTH), sizeof(float));
        file.write(reinterpret_cast<char*>(&SANITY), sizeof(float));
        file.write(reinterpret_cast<char*>(&BATTERY), sizeof(float));
        file.write(reinterpret_cast<char*>(&MASTER_VOLUME), sizeof(float));
        file.write(reinterpret_cast<char*>(&SODA_COUNT), sizeof(int));
        file.write(reinterpret_cast<char*>(&SPARE_BATTERIES), sizeof(int));
        file.write(reinterpret_cast<char*>(&DEATH_COUNT), sizeof(int));
        file.write(reinterpret_cast<char*>(&GRAPHICS_QUALITY), sizeof(int));
        file.close();
    }
}

void executeBinaryLoad(const char* path) {
    std::ifstream file(path, std::ios::binary | std::ios::in);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&HEALTH), sizeof(float));
        file.read(reinterpret_cast<char*>(&SANITY), sizeof(float));
        file.read(reinterpret_cast<char*>(&BATTERY), sizeof(float));
        file.read(reinterpret_cast<char*>(&MASTER_VOLUME), sizeof(float));
        file.read(reinterpret_cast<char*>(&SODA_COUNT), sizeof(int));
        file.read(reinterpret_cast<char*>(&SPARE_BATTERIES), sizeof(int));
        file.read(reinterpret_cast<char*>(&DEATH_COUNT), sizeof(int));
        file.read(reinterpret_cast<char*>(&GRAPHICS_QUALITY), sizeof(int));
        file.close();
    }
}

bool checkSaveExists(const char* path) {
    std::ifstream file(path);
    return file.good();
}

#include <cstdio>

bool executeDeleteSave(const char* path) {
    if (remove(path) == 0) {
        // Reset local variables to default so the session is clean
        HEALTH = 100.0f;
        SANITY = 100.0f;
        BATTERY = 100.0f;
        DEATH_COUNT = 0;
        SODA_COUNT = 0;
        SPARE_BATTERIES = 0;
        return true;
    }
    return false;
}
