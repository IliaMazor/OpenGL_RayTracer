#pragma once

// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Math
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Standard
#include <iostream>
#include <string>

// Function declarations (implemented in main.cpp)
extern void init();
extern void render();
extern void cleanup();
extern void framebufferSizeCallback(GLFWwindow* window, int width, int height);
