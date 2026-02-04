#include "scene.h"
#include "global.h"
#include <glm/gtc/type_ptr.hpp>

Scene::Scene() {
    // Light
    lightSource = glm::vec3(45.0f, 30.0f, 80.0f);

    // Plane (green ground)
    plane.point = glm::vec3(0.0f, -5.0f, 0.0f);
    plane.normal = glm::vec3(0.0f, 1.0f, 0.0f);
    plane.color = glm::vec3(0.0f, 1.0f, 0.0f);
    plane.reflectivity = 0.0f;

    // Sphere (pink, reflective)
    sphere.center = glm::vec3(-1.0f, 0.0f, 10.0f);
    sphere.radius = 5.0f;
    sphere.color = glm::vec3(1.0f, 0.0f, 0.5f);
    sphere.reflectivity = 1.0f;

    // Cylinder (blue)
    cylinder.center = glm::vec3(10.0f, 10.0f, 3.0f);
    cylinder.radius = 1.0f;
    cylinder.height = 4.0f;
    cylinder.color = glm::vec3(0.35f, 0.15f, 1.0f);
    cylinder.reflectivity = 0.0f;

    // Cube (magenta)
    cube.center = glm::vec3(5.0f, 5.0f, 5.0f);
    cube.sideLength = 4.0f;
    cube.color = glm::vec3(1.0f, 0.0f, 0.75f);
    cube.reflectivity = 0.0f;
}

void Scene::cacheUniforms(GLuint program) {
    // Light
    uLightSource = glGetUniformLocation(program, "lightSource");

    // Plane
    uPlanePoint = glGetUniformLocation(program, "planePoint");
    uPlaneNormal = glGetUniformLocation(program, "planeNormal");
    uPlaneColor = glGetUniformLocation(program, "planeColor");

    // Sphere
    uSphereCenter = glGetUniformLocation(program, "sphereCenter");
    uSphereRadius = glGetUniformLocation(program, "sphereRadius");
    uSphereColor = glGetUniformLocation(program, "sphereColor");
    uSphereReflectivity = glGetUniformLocation(program, "sphereReflectivity");

    // Cylinder
    uCylinderCenter = glGetUniformLocation(program, "cylinderCenter");
    uCylinderRadius = glGetUniformLocation(program, "cylinderRadius");
    uCylinderHeight = glGetUniformLocation(program, "cylinderHeight");
    uCylinderColor = glGetUniformLocation(program, "cylinderColor");

    // Cube
    uCubeCenter = glGetUniformLocation(program, "cubeCenter");
    uCubeLength = glGetUniformLocation(program, "cubeLength");
    uCubeColor = glGetUniformLocation(program, "cubeColor");
}

void Scene::sendUniforms() {
    // Light
    glUniform3fv(uLightSource, 1, glm::value_ptr(lightSource));

    // Plane
    glUniform3fv(uPlanePoint, 1, glm::value_ptr(plane.point));
    glUniform3fv(uPlaneNormal, 1, glm::value_ptr(plane.normal));
    glUniform3fv(uPlaneColor, 1, glm::value_ptr(plane.color));

    // Sphere
    glUniform3fv(uSphereCenter, 1, glm::value_ptr(sphere.center));
    glUniform1f(uSphereRadius, sphere.radius);
    glUniform3fv(uSphereColor, 1, glm::value_ptr(sphere.color));
    glUniform1f(uSphereReflectivity, sphere.reflectivity);

    // Cylinder
    glUniform3fv(uCylinderCenter, 1, glm::value_ptr(cylinder.center));
    glUniform1f(uCylinderRadius, cylinder.radius);
    glUniform1f(uCylinderHeight, cylinder.height);
    glUniform3fv(uCylinderColor, 1, glm::value_ptr(cylinder.color));

    // Cube
    glUniform3fv(uCubeCenter, 1, glm::value_ptr(cube.center));
    glUniform1f(uCubeLength, cube.sideLength);
    glUniform3fv(uCubeColor, 1, glm::value_ptr(cube.color));
}
