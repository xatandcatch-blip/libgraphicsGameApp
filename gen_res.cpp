#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

struct ResTable_header {
    uint16_t type;
    uint16_t headerSize;
    uint32_t size;
    uint32_t packageCount;
};

int main() {
    std::ofstream file("game_resources.arsc", std::ios::binary);
    if (!file) return 1;
    
    ResTable_header header = {0x0002, 12, 42, 1}; 
    file.write(reinterpret_cast<char*>(&header), sizeof(header));
    
    std::string name = "libgraphicsGame";
    for(char c : name) {
        file.put(c);
        file.put(0); 
    }
    
    file.close();
    std::cout << "Successfully created game_resources.arsc" << std::endl;
    return 0;
}
