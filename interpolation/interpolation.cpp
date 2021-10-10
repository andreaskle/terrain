#include "interpolation.h"

#include <algorithm>
glm::vec3 PiecewiseLinearInterpolation(float t, const std::vector<glm::vec3>& points, const std::vector<float>& times) {
    if (t <= times.front()) {
        return points.front();
    } else if (t >= times.back()) {
        return points.back();
    }
    auto it = std::upper_bound(times.begin(), times.end(), t);
    auto i = std::distance(times.begin(), std::prev(it));
    float u = (t - times[i]) / (times[i + 1] - times[i]);
    return (1 - u) * points[i] + u * points[i + 1];
}