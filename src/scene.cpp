#include "scene.h"
#include <GLAD/glad.h>


Scene::Scene(){
    eye= glm::vec3(0.0f, 0.0f, 60.0f);
    screen_size = glm::vec2(800.0f,800.0f);
    light_source= glm::vec3(45.0f, 30.0f, 80.0f);

    L= -10.0f;
    R= 10.0f; 
    T= 10.0f;
    B= -10.0f;
    N= 16.0f;


    plane.point = glm::vec3(0.0f, -5.0f, 0.0f);    
    plane.normal = glm::vec3(0., 1.0, 0.0f);
    plane.color = glm::vec3(0.0f, 1.0f, 0.0f);

    sphere.center = glm::vec3(-1.0f, 0.0f, 2.0f);
    sphere.radius = 5.0f;
    sphere.color = glm::vec3(1.0f, 0.0f, 0.5f);

    cylinder.center = glm::vec3(10.0f, 10.0f, 3.0f);
    cylinder.radius = 1;
    cylinder.height = 4;
    cylinder.color= glm::vec3(.35f, .15f, 1.0f);
    
    cube.center = glm::vec3(5.0f,5.0f, 5.0f);
    cube.cube_len = 4;
    cube.color = glm::vec3(1.0f, 0.0f, .75f);


}

void Scene::sendUniforms(unsigned int shader) {
    // camera
    glUniform3f(glGetUniformLocation(shader, "eye"), eye.x, eye.y, eye.z);
    glUniform2f(glGetUniformLocation(shader, "screen_size"), screen_size.x, screen_size.y);
    glUniform1f(glGetUniformLocation(shader, "L"), L);
    glUniform1f(glGetUniformLocation(shader, "R"), R);
    glUniform1f(glGetUniformLocation(shader, "B"), B);
    glUniform1f(glGetUniformLocation(shader, "T"), T);
    glUniform1f(glGetUniformLocation(shader, "N"), N);
    
    // light
    glUniform3f(glGetUniformLocation(shader, "light_source"), light_source.x, light_source.y, light_source.z);
    
    // plane
    glUniform3f(glGetUniformLocation(shader, "planePoint"), plane.point.x, plane.point.y, plane.point.z);
    glUniform3f(glGetUniformLocation(shader, "planeNormal"), plane.normal.x, plane.normal.y, plane.normal.z);
    glUniform3f(glGetUniformLocation(shader, "planeColor"), plane.color.x, plane.color.y, plane.color.z);
    
    // sphere
    glUniform3f(glGetUniformLocation(shader, "sphereCenter"), sphere.center.x, sphere.center.y, sphere.center.z);
    glUniform1f(glGetUniformLocation(shader, "sphereRadius"), sphere.radius);
    glUniform3f(glGetUniformLocation(shader, "sphereColor"), sphere.color.x, sphere.color.y, sphere.color.z);

    //cylinder
    glUniform3f(glGetUniformLocation(shader, "cylinderCenter"), cylinder.center.x, cylinder.center.y, cylinder.center.z);
    glUniform1f(glGetUniformLocation(shader, "cylinderRadius"), cylinder.radius);
    glUniform1f(glGetUniformLocation(shader, "cylinderHeight"), cylinder.height);
    glUniform3f(glGetUniformLocation(shader, "cylinderColor"), cylinder.color.x, cylinder.color.y, cylinder.color.z);


    //cube
    glUniform3f(glGetUniformLocation(shader, "cubeCenter"), cube.center.x, cube.center.y, cube.center.z);
    glUniform1f(glGetUniformLocation(shader, "cubeLength"), cube.cube_len);
    glUniform3f(glGetUniformLocation(shader, "cubeColor"), cube.color.x, cube.color.y, cube.color.z);


}