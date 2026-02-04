#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>

struct Plane {
    glm::vec3 point;
    glm::vec3 normal;
    glm::vec3 color;
    float reflectivity;
};

struct Sphere {
    glm::vec3 center;
    float radius;
    glm::vec3 color;
    float reflectivity;
};

struct Cylinder {
    glm::vec3 center;
    float radius;
    float height;
    glm::vec3 color;
    float reflectivity;
};

struct Cube {
    glm::vec3 center;
    float sideLength;
    glm::vec3 color;
    float reflectivity;
};

class Scene {
public:
    // Light
    glm::vec3 lightSource;

    // Objects
    Plane plane;
    Sphere sphere;
    Cylinder cylinder;
    Cube cube;

    Scene();

    // Call once after shader is compiled to cache uniform locations
    void cacheUniforms(GLuint program);

    // Call to send all scene data to GPU
    void sendUniforms();
};
