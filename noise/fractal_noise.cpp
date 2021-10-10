#include "fractal_noise.h"

#include <algorithm>
#include <numeric>
#include <random>

#include "perlin_noise.h"
float fBm(const PerlinNoise& noise, const glm::vec2& p, int octaves) {
    float frequency = 1.0;
    float amplitude = 0.5;
    float lacunarity = 2.0;
    float gain = 0.5;
    float result = 0;
    for (int i = 0; i < octaves; ++i) {
        result += amplitude * noise.Value(frequency * p);
        frequency *= lacunarity;
        amplitude *= gain;
    }
    return result;
}
