#pragma once

struct GLFWwindow;  // Forward declaration
class Camera;       // Forward declaration

namespace Input {
    // Initialize input system with window and camera reference
    void init(GLFWwindow* window, Camera* camera);

    // Process keyboard input (call each frame)
    void processInput(GLFWwindow* window, float deltaTime);

    // GLFW callbacks
    void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
}
