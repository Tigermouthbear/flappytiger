//
// Created by Tigermouthbear on 12/28/20.
//

#ifndef FLAPPYTIGER_STATICMESH_H
#define FLAPPYTIGER_STATICMESH_H


#include <vector>
#include "Buffer.h"
#include "Point.h"

class StaticMesh: public Buffer {
private:
    void build(std::vector<GLfloat>* vertices, std::vector<unsigned int>* indices);

public:
    StaticMesh(std::vector<Point>* points, std::vector<unsigned int>* indices);

    StaticMesh(std::vector<GLfloat>* vertices, std::vector<unsigned int>* indices);

    void render() override;
};


#endif //FLAPPYTIGER_STATICMESH_H
