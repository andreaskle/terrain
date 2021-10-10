#include "perlin_noise.h"

#include <algorithm>
#include <random>

PerlinNoise::PerlinNoise(uint32_t seed) {
    grid.resize(256 * 256);

    std::mt19937 gen(seed);
    std::uniform_real_distribution dist(0.0, 1.0);
    std::generate(grid.begin(), grid.end(), [&] {
        float theta = 2 * M_PI * dist(gen);
        return glm::normalize(glm::vec2(std::cos(theta), std::sin(theta)));
    });
}
// fade based on Ken Perlin's Improving Noise paper
double fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}
int index(int x, int y) {
    int i = x & 255;
    int j = y & 255;
    return (i + j * 256);
}
glm::vec2 PerlinNoise::grad(const glm::vec2& p) const {
    return grid[index(p.x, p.y)];
}
double PerlinNoise::Value(const glm::vec2& p) const {
    glm::vec2 p0 = glm::floor(p);
    glm::vec2 p1 = p0 + glm::vec2(1, 0);
    glm::vec2 p2 = p0 + glm::vec2(0, 1);
    glm::vec2 p3 = p0 + glm::vec2(1, 1);

    glm::vec2 g0 = grid[index(p0.x, p0.y)];
    glm::vec2 g1 = grid[index(p1.x, p1.y)];
    glm::vec2 g2 = grid[index(p2.x, p2.y)];
    glm::vec2 g3 = grid[index(p3.x, p3.y)];

    double u = fade(p.x - p0.x);
    double v = fade(p.y - p0.y);

    double a = (1 - u) * glm::dot(g0, p - p0) + u * glm::dot(g1, p - p1);
    double b = (1 - u) * glm::dot(g2, p - p2) + u * glm::dot(g3, p - p3);
    return (1 - v) * a + v * b;
}