#pragma once
#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <fstream>
#include <sstream>
#include <string>

#include <vector>



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void generateWindow();

unsigned int make_module(const std::string& file_path, unsigned int type);
unsigned int make_shader(const std::string& file_path, const std::string& fragment_filepath);
