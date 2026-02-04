#pragma once
#include <glad/glad.h>

class ScreenQuad {
public:
    ScreenQuad();
    ~ScreenQuad();

    void draw();

private:
    GLuint VAO;
    GLuint VBO;
};
