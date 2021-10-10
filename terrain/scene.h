#ifndef SCENE_H
#define SCENE_H
#include "camera.h"
#include "glad/glad.h"
#include "glm/glm.hpp"

class Scene {
   public:
    ~Scene();
    void Init(int width, int height);
    void Render(float dt);
    void ToggleWireframe();
    void TogglePause() {
        pause = !pause;
    }
    void IncreaseTessFactor() {
        tessFactor++;
        tessFactor = std::min(tessFactor, 6.0f);
    }
    void DecreaseTessFactor() {
        tessFactor--;
        tessFactor = std::max(tessFactor, 0.0f);
    }

   private:
    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;
    GLuint tessellationControlShader = 0;
    GLuint tessellationEvaluationShader = 0;
    GLuint shaderProgram = 0;
    GLuint vertexBuffer = 0;
    GLuint indexBuffer = 0;
    GLuint vertexArrayObject = 0;
    GLuint heightMap = 0;

    Camera camera;
    float time = 0;
    float maxTime = 10;
    int heightMapWidth = 1024;
    int heightMapHeight = 1024;

    bool wireFrame = false;
    float tessFactor = 0.0f;
    uint32_t numIndices = 0;
    bool pause = false;

    glm::vec3 GetCameraPath(float t) const;
    void Update(float dt);

    void CreateHeightMap();

    void CreateGridGeometry();
};
#endif
