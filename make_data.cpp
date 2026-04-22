#include <fstream>
#include <string>

int main() {
    std::ofstream file("data.cpp");
    if (!file) return 1;

    file << "/* libgraphicsGame Native Data Map */\n";
    file << "#include <stdint.h>\n\n";
    
    file << "extern \"C\" {\n";
    file << "    int32_t PLAYER_HEALTH = 100;\n";
    file << "    int32_t PLAYER_LEVEL = 1;\n";
    file << "    int32_t PLAYER_XP = 0;\n";
    file << "    int32_t PLAYER_STAMINA = 100;\n";
    file << "    const char* PLAYER_NAME = \"RuneWarrior\";\n";
    file << "    const char* ENGINE_VERSION = \"v1.0.92-PRO\";\n";
    file << "    bool IS_SFD_LOADED = true;\n";
    file << "}\n";
    
    file.close();
    return 0;
}
