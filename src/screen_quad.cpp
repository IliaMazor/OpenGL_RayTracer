#include "screen_quad.h"

ScreenQuad::ScreenQuad() {
    // Full-screen quad (two triangles)
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,   // bottom-left
         1.0f, -1.0f, 0.0f,   // bottom-right
        -1.0f,  1.0f, 0.0f,   // top-left
         1.0f, -1.0f, 0.0f,   // bottom-right
         1.0f,  1.0f, 0.0f,   // top-right
        -1.0f,  1.0f, 0.0f    // top-left
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO
    glBindVertexArray(0);
}

ScreenQuad::~ScreenQuad() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void ScreenQuad::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
