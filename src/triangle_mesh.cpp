#include "triangle_mesh.h"
#include <vector>
#include <GLAD/glad.h>

TriangleMesh::TriangleMesh() {
    // Define a simple triangle with positions and colors
    //star shape
    // std::vector<float> data = {
    //     -0.5f, -0.5f, 0.0f, 
    //     -0.25f, 0.0f, 0.0f,
    //     -0.5f, 0.5f, 0.0f,
    //     0.0f,  0.75f, 0.0f,
    //     0.5f, 0.5f, 0.0f,
    //     0.25f, 0.0f, 0.0f,
    //     0.5f, -0.5f, 0.0f   
    // };

    // vertex_count = 7;
    std::vector<float> data = {
        -1.0f, -1.0f, 0.0f,   // bottom-left
        1.0f, -1.0f, 0.0f,   // bottom-right
        -1.0f,  1.0f, 0.0f,   // top-left
        1.0f, -1.0f, 0.0f,   // bottom-right
        1.0f,  1.0f, 0.0f,   // top-right
        -1.0f,  1.0f, 0.0f    // top-left
    };
    // std::vector<float> data = {
    //     -0.5f, -0.5f, 0.0f,   // bottom-left
    //     0.0f, 0.5f, 0.0f,   // bottom-right
    //     0.5f,  -0.5f, 0.0f   // top-left
    // };

    vertex_count = 6;

    // Generate and bind VAO and VBO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // 
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    size_t bufferSize = data.size() * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, data.data(), GL_STATIC_DRAW);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);
}

void TriangleMesh::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
