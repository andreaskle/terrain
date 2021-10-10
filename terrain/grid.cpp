#include "grid.h"
void CreateGrid(int numTilesX, int numTilesZ, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
    float xOff = numTilesX / 2.0f;
    float zOff = numTilesZ / 2.0f;
    for (int x = 0; x < numTilesX; ++x) {
        for (int z = 0; z < numTilesZ; ++z) {
            Vertex vx;
            vx.pos = glm::vec3(x - xOff, 0, z - zOff) * 0.5f;
            vx.normal = glm::vec3(0, 1, 0);
            vx.uv = glm::vec2(x / float(numTilesX - 1), z / float(numTilesZ - 1));
            vertices.push_back(vx);
        }
    }
    for (int z = 0; z < numTilesZ - 1; ++z) {
        for (int x = 0; x < numTilesX - 1; ++x) {
            indices.push_back(x + (z + 1) * numTilesX);
            indices.push_back(x + z * numTilesX);
            indices.push_back(x + 1 + (z + 1) * numTilesX);
            indices.push_back(x + 1 + (z + 1) * numTilesX);
            indices.push_back(x + z * numTilesX);
            indices.push_back(x + 1 + z * numTilesX);
        }
    }
}