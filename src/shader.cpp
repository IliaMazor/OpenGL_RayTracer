#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

static std::string readFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "ERROR: Failed to open shader file: " << filepath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

static GLuint compileShader(const std::string& source, GLenum type, const std::string& name) {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, log);
        std::cerr << "ERROR: " << name << " compilation failed:\n" << log << std::endl;
        return 0;
    }
    return shader;
}

GLuint InitShader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertSrc = readFile(vertexPath);
    std::string fragSrc = readFile(fragmentPath);

    if (vertSrc.empty() || fragSrc.empty()) {
        return 0;
    }

    GLuint vertShader = compileShader(vertSrc, GL_VERTEX_SHADER, vertexPath);
    GLuint fragShader = compileShader(fragSrc, GL_FRAGMENT_SHADER, fragmentPath);

    if (vertShader == 0 || fragShader == 0) {
        return 0;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetProgramInfoLog(program, 1024, nullptr, log);
        std::cerr << "ERROR: Shader linking failed:\n" << log << std::endl;
        return 0;
    }

    // Cleanup shader objects after linking
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;
}
