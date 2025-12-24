#pragma once

#include <glm/glm.hpp>

struct PlaneData{
    glm::vec3 point;
    glm::vec3 normal;
    glm::vec3 color;
};


struct Sphere{
    glm::vec3 center;
    float radius;
    glm::vec3 color;
};


class Scene{
public:
    glm::vec3 eye;
    glm::vec2 screen_size;
    glm::vec3 light_source;
    float L, R , B , T , N;

    PlaneData plane;
    Sphere sphere;

    


    Scene();
    void sendUniforms(unsigned int shader);


};