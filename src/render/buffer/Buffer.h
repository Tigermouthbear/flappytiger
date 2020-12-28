//
// Created by Tigermouthbear on 12/28/20.
//

#ifndef FLAPPYTIGER_BUFFER_H
#define FLAPPYTIGER_BUFFER_H

#include <GL/glew.h>

class Buffer {
protected:
    // basic variables for rendering, you dont need to use these, although using the VAO, VBO, IBO vars is preferred
    // as the buffers are deleted when this buffers deconstructor is called
    GLuint VAO{}, VBO{}, IBO{}, indexCount{}, vertexCount{};

public:
    virtual void render() = 0;

    ~Buffer() {
        if(IBO != 0) {
            glDeleteBuffers(1, &IBO);
            IBO = 0;
        }

        if(VBO != 0) {
            glDeleteBuffers(1, &VBO);
            VBO = 0;
        }

        if(VAO != 0) {
            glDeleteVertexArrays(1, &VAO);
            VAO = 0;
        }
    }
};


#endif //FLAPPYTIGER_BUFFER_H
