#include <stdint.h>

extern "C" {
    // Survival Database
    int32_t PLAYER_HEALTH = 100;
    
    // NPC Entity Data
    bool ENTITY_SPAWNED = false;
    float ENTITY_POS_Z = 0.0f;

    // Vertex Structure for the Mansion Entity
    struct Vertex {
        float pos[3];
        float color[3];
    };

    // The "Shape" of the horror (A simple 3D prism)
    Vertex entityVertices[] = {
        {{ 0.0f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}}, // Top (Blood Red)
        {{ 0.5f,  0.5f, 0.0f}, {0.1f, 0.0f, 0.0f}}, // Bottom Right
        {{-0.5f,  0.5f, 0.0f}, {0.1f, 0.0f, 0.0f}}  // Bottom Left
    };

    void spawnMansionEntity(float x, float y, float z) {
        ENTITY_SPAWNED = true;
        ENTITY_POS_Z = z;
    }

    void updateAI() {
        if (ENTITY_SPAWNED) {
            ENTITY_POS_Z += 0.05f; // Incremental creep
        }
    }
}
