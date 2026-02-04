#include "camera.h"
#include "global.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

Camera::Camera() {
    // Initial position and orientation
    position = glm::vec3(0.0f, 0.0f, 60.0f);
    yaw = -90.0f;   // Looking toward -Z initially
    pitch = 0.0f;

    // Movement settings
    moveSpeed = 20.0f;
    mouseSensitivity = 0.1f;

    // View frustum settings
    L = -10.0f;
    R = 10.0f;
    B = -10.0f;
    T = 10.0f;
    N = 16.0f;
    screenSize = glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Calculate initial direction vectors
    updateVectors();
}

void Camera::updateVectors() {
    // Calculate front vector from yaw and pitch (spherical to cartesian)
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    // Recalculate right and up vectors
    // Right is perpendicular to front and world up
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    // Up is perpendicular to right and front
    up = glm::normalize(glm::cross(right, front));
}

void Camera::processKeyboard(int key, float deltaTime) {
    float velocity = moveSpeed * deltaTime;

    // WASD movement relative to camera orientation
    if (key == GLFW_KEY_W) {
        position += front * velocity;
    }
    if (key == GLFW_KEY_S) {
        position -= front * velocity;
    }
    if (key == GLFW_KEY_A) {
        position -= right * velocity;
    }
    if (key == GLFW_KEY_D) {
        position += right * velocity;
    }
    // Vertical movement (world space)
    if (key == GLFW_KEY_SPACE) {
        position.y += velocity;
    }
    if (key == GLFW_KEY_LEFT_SHIFT) {
        position.y -= velocity;
    }
}

void Camera::processMouse(float xOffset, float yOffset) {
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    // Constrain pitch to avoid gimbal lock / flipping
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    updateVectors();
}

void Camera::cacheUniforms(GLuint program) {
    uEye = glGetUniformLocation(program, "eye");
    uScreenSize = glGetUniformLocation(program, "screenSize");
    uL = glGetUniformLocation(program, "L");
    uR = glGetUniformLocation(program, "R");
    uB = glGetUniformLocation(program, "B");
    uT = glGetUniformLocation(program, "T");
    uN = glGetUniformLocation(program, "N");
    uCameraFront = glGetUniformLocation(program, "cameraFront");
    uCameraRight = glGetUniformLocation(program, "cameraRight");
    uCameraUp = glGetUniformLocation(program, "cameraUp");
}

void Camera::sendUniforms() {
    glUniform3fv(uEye, 1, glm::value_ptr(position));
    glUniform2fv(uScreenSize, 1, glm::value_ptr(screenSize));
    glUniform1f(uL, L);
    glUniform1f(uR, R);
    glUniform1f(uB, B);
    glUniform1f(uT, T);
    glUniform1f(uN, N);
    glUniform3fv(uCameraFront, 1, glm::value_ptr(front));
    glUniform3fv(uCameraRight, 1, glm::value_ptr(right));
    glUniform3fv(uCameraUp, 1, glm::value_ptr(up));
}
