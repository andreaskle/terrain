#ifndef NOISE_FRACTAL_NOISE_H_
#define NOISE_FRACTAL_NOISE_H_
#include "glm/glm.hpp"
class PerlinNoise;

float fBm(const PerlinNoise& noise, const glm::vec2& p, int octaves);

#endif
