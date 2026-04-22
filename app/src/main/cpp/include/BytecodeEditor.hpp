#ifndef BYTECODE_EDITOR_HPP
#define BYTECODE_EDITOR_HPP

#include <vector>
#include <cstdint>

class BytecodeEditor {
public:
    // Finds and replaces Smali opcodes or Resource strings in hex
    void patchBytecode(std::vector<uint8_t>& data, uint8_t target, uint8_t replacement) {
        for (auto &byte : data) {
            if (byte == target) byte = replacement;
        }
    }
};

#endif
