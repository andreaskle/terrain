#include "catch2/catch.hpp"
#include "glm/gtc/epsilon.hpp"
#include "interpolation/interpolation.h"
const float eps = 0.00001f;

void Vec3Equal(const glm::vec3& left, const glm::vec3& right) {
    for (int i = 0; i < 3; ++i) {
        REQUIRE(left[i] == Approx(right[i]));
    }
}

TEST_CASE("Piecewise Linear Interpolation") {
    std::vector<glm::vec3> points{glm::vec3(0, 0, 0), glm::vec3(1, 1, 0), glm::vec3(3, -1, 0), glm::vec3(5, 1.5, 0)};
    std::vector<float> times{0, 1, 2, 3};
    // Test the control points
    for (std::size_t i = 0; i < points.size(); ++i) {
        Vec3Equal(PiecewiseLinearInterpolation(times[i], points, times), points[i]);
    }

    Vec3Equal(PiecewiseLinearInterpolation(0.5f, points, times), points[0] * 0.5f + points[1] * 0.5f);
    Vec3Equal(PiecewiseLinearInterpolation(1.5f, points, times), points[1] * 0.5f + points[2] * 0.5f);
    Vec3Equal(PiecewiseLinearInterpolation(2.5f, points, times), points[2] * 0.5f + points[3] * 0.5f);
    Vec3Equal(PiecewiseLinearInterpolation(-1, points, times), points.front());
    Vec3Equal(PiecewiseLinearInterpolation(4, points, times), points.back());
}