//
// Created by Tigermouthbear on 12/28/20.
//

#ifndef FLAPPYTIGER_DYNAMICMESH_H
#define FLAPPYTIGER_DYNAMICMESH_H

#include <vector>
#include "Buffer.h"

class DynamicMesh: public Buffer {
private:
    std::vector<GLfloat>* vertices;

public:
    DynamicMesh(std::vector<GLfloat>* vertices, std::vector<unsigned int>* indices);

    void render() override;
};


#endif //FLAPPYTIGER_DYNAMICMESH_H
