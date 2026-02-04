#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>

class Camera {
public:
    Camera();

    // Position and orientation
    glm::vec3 position;
    float yaw;    // Horizontal rotation (degrees)
    float pitch;  // Vertical rotation (degrees)

    // Movement settings
    float moveSpeed;
    float mouseSensitivity;

    // View frustum (for ray generation)
    float L, R, B, T, N;
    glm::vec2 screenSize;

    // Computed directions (recalculated from yaw/pitch)
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    // Methods
    void updateVectors();  // Recalculate front/right/up from yaw/pitch
    void processKeyboard(int key, float deltaTime);
    void processMouse(float xOffset, float yOffset);

    // Uniform management
    void cacheUniforms(GLuint program);
    void sendUniforms();

private:
    // Cached uniform locations
    GLint uEye;
    GLint uScreenSize;
    GLint uL, uR, uB, uT, uN;
    GLint uCameraFront;
    GLint uCameraRight;
    GLint uCameraUp;
};
