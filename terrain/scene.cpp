#include "scene.h"
#define STB_IMAGE_IMPLEMENTATION

#include "glm/gtc/type_ptr.hpp"
#include "grid.h"
#include "interpolation/interpolation.h"
#include "noise/fractal_noise.h"
#include "noise/perlin_noise.h"
#include "opengl/utils.h"
#include "stb_image.h"
#include "vertex.h"
Scene::~Scene() {
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(tessellationEvaluationShader);
    glDeleteShader(tessellationControlShader);
    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteTextures(1, &heightMap);
}

void Scene::CreateGridGeometry() {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    CreateGrid(40, 40, vertices, indices);
    numIndices = indices.size();

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(2 * sizeof(glm::vec3)));
    glBindVertexArray(0);
}

void Scene::CreateHeightMap() {
    // Create a height map image using fractional brownian motion
    std::vector<float> image;
    image.resize(heightMapWidth * heightMapHeight);
    PerlinNoise noise(0);
    for (int i = 0; i < heightMapWidth; i++) {
        for (int j = 0; j < heightMapHeight; j++) {
            double x = (heightMapWidth * 0.5 - i) / (heightMapWidth * 0.5);
            double y = (heightMapHeight * 0.5 - j) / (heightMapHeight * 0.5);
            image[i + j * heightMapWidth] = std::max(0.0f, fBm(noise, glm::vec2(x, y), 8));
        }
    }

    glGenTextures(1, &heightMap);
    glBindTexture(GL_TEXTURE_2D, heightMap);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, heightMapWidth, heightMapHeight, 0, GL_RED, GL_FLOAT, image.data());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
}

void Scene::Init(int width, int height) {
    vertexShader = CreateShaderFromFile(GL_VERTEX_SHADER, "terrain/shaders/vertex.glsl");
    fragmentShader = CreateShaderFromFile(GL_FRAGMENT_SHADER, "terrain/shaders/fragment.glsl");
    tessellationControlShader = CreateShaderFromFile(GL_TESS_CONTROL_SHADER, "terrain/shaders/tesscontrol.glsl");
    tessellationEvaluationShader = CreateShaderFromFile(GL_TESS_EVALUATION_SHADER, "terrain/shaders/tesseval.glsl");
    shaderProgram =
        CreateProgram({vertexShader, fragmentShader, tessellationControlShader, tessellationEvaluationShader});

    CreateGridGeometry();

    CreateHeightMap();

    glClearColor(0.4f, 0.4f, 0.6f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
    camera.perspective(width, height);

    glPatchParameteri(GL_PATCH_VERTICES, 3);
}

void Scene::Render(float dt) {
    Update(dt);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glUseProgram(shaderProgram);

    glm::mat4 mvpMatrix = camera.GetViewProjMatrix();

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "mvpMatrix"), 1, GL_FALSE, glm::value_ptr(mvpMatrix));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, heightMap);

    glUniform1i(glGetUniformLocation(shaderProgram, "heightMap"), 0);
    glUniform1f(glGetUniformLocation(shaderProgram, "tessFactor"), std::pow(2.0f, tessFactor));
    glDrawElements(GL_PATCHES, numIndices, GL_UNSIGNED_INT, 0);
    glUseProgram(0);

    glBindVertexArray(0);
}

glm::vec3 Scene::GetCameraPath(float t) const {
    std::vector<glm::vec3> points{glm::vec3(0, 10, 15), glm::vec3(0, 10, 5.0), glm::vec3(5, 10, -2.0)};
    std::vector<float> times{0, 5, 10};
    return PiecewiseLinearInterpolation(t, points, times);
}

void Scene::ToggleWireframe() {
    wireFrame = !wireFrame;
    glPolygonMode(GL_FRONT_AND_BACK, wireFrame ? GL_LINE : GL_FILL);
}

void Scene::Update(float dt) {
    if (!pause) {
        time += dt;
    }

    if (time > maxTime) {
        time = 0;
    }
    glm::vec3 pos = GetCameraPath(time);
    camera.SetPosition(pos);
    camera.SetTarget(pos + glm::vec3(0, -1, -1));
}
