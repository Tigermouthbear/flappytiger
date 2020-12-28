//
// Created by Tigermouthbear on 12/28/20.
//

#include "DynamicMesh.h"

DynamicMesh::DynamicMesh(std::vector<GLfloat>* vertices, std::vector<unsigned int>* indices) {
    this->vertices = vertices;
    this->vertexCount = vertices->size();
    this->indexCount = indices->size();

    unsigned int indicesArray[indexCount];
    std::copy(indices->begin(), indices->end(), indicesArray);

    // create and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // create, bind, and write to IBO
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesArray[0]) * indexCount, &indicesArray, GL_STATIC_DRAW);

    // create, bind, and write to VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(0.0F) * vertices->size(), nullptr, GL_DYNAMIC_DRAW);

    // define what data to use
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(0.0F) * 5, nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(0.0F) * 5, (void*) (sizeof(0.0F) * 3));
    glEnableVertexAttribArray(1);

    // unbind everything
    glBindBuffer(GL_ARRAY_BUFFER, 0); // vbo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // ibo
    glBindVertexArray(0); // vao
}

void DynamicMesh::render() {
    // bind vao ibo and vbo
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // update vbo and draw
    GLfloat verticesArray[vertexCount];
    std::copy(vertices->begin(), vertices->end(), verticesArray);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verticesArray[0]) * vertexCount, verticesArray);

    // draw
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

    // unbind vao vbo and ibo
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
