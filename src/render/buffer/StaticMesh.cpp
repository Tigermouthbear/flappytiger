//
// Created by Tigermouthbear on 12/28/20.
//

#include "StaticMesh.h"

StaticMesh::StaticMesh(std::vector<Point>* points, std::vector<unsigned int>* indices) {
    auto* vertices = new std::vector<GLfloat>();
    for(Point point: *points) {
        vertices->push_back(point.X);
        vertices->push_back(point.Y);
        vertices->push_back(point.Z);
        vertices->push_back(point.UX);
        vertices->push_back(point.UY);
    }

    build(vertices, indices);
}

StaticMesh::StaticMesh(std::vector<GLfloat>* vertices, std::vector<unsigned int>* indices) {
    build(vertices, indices);
}

void StaticMesh::build(std::vector<GLfloat>* vertices, std::vector<unsigned int>* indices) {
    VAO = 0;
    VBO = 0;
    IBO = 0;

    vertexCount = vertices->size();
    indexCount = indices->size();

    GLfloat verticesArray[vertexCount];
    std::copy(vertices->begin(), vertices->end(), verticesArray);

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArray[0]) * vertexCount, &verticesArray, GL_STATIC_DRAW);

    // define what data to use
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(verticesArray[0]) * 5, nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(verticesArray[0]) * 5,
                          (void*) (sizeof(verticesArray[0]) * 3));
    glEnableVertexAttribArray(1);

    // unbind everything
    glBindBuffer(GL_ARRAY_BUFFER, 0); // vbo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // ibo
    glBindVertexArray(0); // vao
}

void StaticMesh::render() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}