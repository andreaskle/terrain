#ifndef NOISE_PERLIN_NOISE_H_
#define NOISE_PERLIN_NOISE_H_
#include <cstdint>
#include <vector>

#include "glm/glm.hpp"
class PerlinNoise {
   public:
    PerlinNoise(uint32_t seed);

    double Value(const glm::vec2& p) const;

   private:
    std::vector<glm::vec2> grid;
    glm::vec2 grad(const glm::vec2& p) const;
};
#endif