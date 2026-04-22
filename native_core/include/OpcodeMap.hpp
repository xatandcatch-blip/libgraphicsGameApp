#ifndef OPCODE_MAP_HPP
#define OPCODE_MAP_HPP

#include <map>
#include <string>

// Separated from JNI to avoid conflicts during heavy compilation
class OpcodeMap {
public:
    std::map<std::string, uint8_t> smaliToHex = {
        {"nop", 0x00},
        {"move", 0x01},
        {"return-void", 0x0E},
        {"const/4", 0x12}
    };
};

#endif
