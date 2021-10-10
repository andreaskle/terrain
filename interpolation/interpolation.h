#include <vector>

#include "glm/glm.hpp"

glm::vec3 PiecewiseLinearInterpolation(float t, const std::vector<glm::vec3>& points, const std::vector<float>& times);
