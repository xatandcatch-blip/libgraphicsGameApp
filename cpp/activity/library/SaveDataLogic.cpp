#include <fstream>
#include <stdint.h>
#include <cstdio>

extern float HEALTH, SANITY, BATTERY, MASTER_VOLUME;
extern int SODA_COUNT, SPARE_BATTERIES, DEATH_COUNT, GRAPHICS_QUALITY;

// Calculate a simple hash of current stats
uint32_t calculateChecksum() {
    uint32_t sum = 0;
    sum += (uint32_t)HEALTH + (uint32_t)SANITY + (uint32_t)BATTERY;
    sum += (uint32_t)SODA_COUNT + (uint32_t)SPARE_BATTERIES + (uint32_t)DEATH_COUNT;
    return sum;
}

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
        
        // Write the checksum at the end
        uint32_t checksum = calculateChecksum();
        file.write(reinterpret_cast<char*>(&checksum), sizeof(uint32_t));
        file.close();
    }
}

bool executeBinaryLoad(const char* path) {
    std::ifstream file(path, std::ios::binary | std::ios::in);
    if (file.is_open()) {
        float h, s, b, v;
        int sc, sb, dc, gq;
        uint32_t storedChecksum, currentChecksum;

        file.read(reinterpret_cast<char*>(&h), sizeof(float));
        file.read(reinterpret_cast<char*>(&s), sizeof(float));
        file.read(reinterpret_cast<char*>(&b), sizeof(float));
        file.read(reinterpret_cast<char*>(&v), sizeof(float));
        file.read(reinterpret_cast<char*>(&sc), sizeof(int));
        file.read(reinterpret_cast<char*>(&sb), sizeof(int));
        file.read(reinterpret_cast<char*>(&dc), sizeof(int));
        file.read(reinterpret_cast<char*>(&gq), sizeof(int));
        file.read(reinterpret_cast<char*>(&storedChecksum), sizeof(uint32_t));
        file.close();

        // Temporary assignment to check integrity
        HEALTH = h; SANITY = s; BATTERY = b; MASTER_VOLUME = v;
        SODA_COUNT = sc; SPARE_BATTERIES = sb; DEATH_COUNT = dc; GRAPHICS_QUALITY = gq;

        currentChecksum = calculateChecksum();
        if (currentChecksum != storedChecksum) {
            return false; // Data tampered with!
        }
        return true;
    }
    return false;
}

bool executeDeleteSave(const char* path) {
    return (remove(path) == 0);
}

bool checkSaveExists(const char* path) {
    std::ifstream file(path);
    return file.good();
}
