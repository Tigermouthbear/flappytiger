//
// Created by Tigermouthbear on 12/28/20.
//

#ifndef FLAPPYTIGER_UNIFORM_H
#define FLAPPYTIGER_UNIFORM_H

#include "Shader.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

class Uniform {
private:
    GLuint uniformID;

public:
    Uniform(const char* name, Shader* shader) {
        uniformID = shader->getUniformLocation(name);
    }

    GLuint getID() const { return uniformID; }

    ~Uniform() {
        uniformID = 0;
    }
};


#endif //FLAPPYTIGER_UNIFORM_H
