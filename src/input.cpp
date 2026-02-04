#include "input.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.h"

namespace Input {

// Static variables for input state
static Camera* g_camera = nullptr;
static bool rightMousePressed = false;
static bool firstMouse = true;
static float lastX = 400.0f;
static float lastY = 400.0f;

void init(GLFWwindow* window, Camera* camera) {
    g_camera = camera;

    // Register callbacks
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    // Initialize mouse position tracking
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);
}

void processInput(GLFWwindow* window, float deltaTime) {
    // ESC to close window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    // WASD movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        g_camera->processKeyboard(GLFW_KEY_W, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        g_camera->processKeyboard(GLFW_KEY_S, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        g_camera->processKeyboard(GLFW_KEY_A, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        g_camera->processKeyboard(GLFW_KEY_D, deltaTime);
    }

    // Vertical movement
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        g_camera->processKeyboard(GLFW_KEY_SPACE, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        g_camera->processKeyboard(GLFW_KEY_LEFT_SHIFT, deltaTime);
    }
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    float xposf = static_cast<float>(xpos);
    float yposf = static_cast<float>(ypos);

    if (firstMouse) {
        lastX = xposf;
        lastY = yposf;
        firstMouse = false;
    }

    // Only rotate camera when right mouse button is held
    if (rightMousePressed) {
        float xOffset = xposf - lastX;
        float yOffset = lastY - yposf;  // Reversed: y increases downward in screen coords

        g_camera->processMouse(xOffset, yOffset);
    }

    lastX = xposf;
    lastY = yposf;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            rightMousePressed = true;
        } else if (action == GLFW_RELEASE) {
            rightMousePressed = false;
        }
    }
}

}  // namespace Input
