//
// Created by Tigermouthbear on 12/28/20.
//

#ifndef FLAPPYTIGER_SHADER_H
#define FLAPPYTIGER_SHADER_H

#include <string>
#include <cstring>
#include <cstdio>
#include <GL/glew.h>

class Shader {
private:
    GLuint shaderID;

    void compile(const char* vertexCode, const char* fragCode);

    void add(const char* shaderCode, GLenum type) const;

public:
    Shader(const char* vertexLocation, const char* fragLocation);

    void attach() const;

    GLuint getUniformLocation(const char* name) const;

    ~Shader();

    static std::string readFile(const std::string& fileLocation);
};


#endif //FLAPPYTIGER_SHADER_H
