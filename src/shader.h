#pragma once
#include <glad/glad.h>
#include <string>

// Compiles and links vertex + fragment shaders, returns program handle
GLuint InitShader(const std::string& vertexPath, const std::string& fragmentPath);
