//
// Created by Tigermouthbear on 12/28/20.
//

#include "Shader.h"

#include <fstream>

Shader::Shader(const char* vertexLocation, const char* fragLocation) {
    shaderID = 0;

    compile(readFile(vertexLocation).c_str(), readFile(fragLocation).c_str());
}

void Shader::compile(const char* vertexCode, const char* fragCode) {
    shaderID = glCreateProgram();

    if(!shaderID) {
        printf("Error Creating Shader!\n");
        return;
    }

    add(vertexCode, GL_VERTEX_SHADER);
    add(fragCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if(!result) {
        glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        printf("Error Linking Program: '%s'\n", eLog);
    }

    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if(!result) {
        glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        printf("Error Validating Program: '%s'\n", eLog);
        return;
    }
}

void Shader::add(const char* shaderCode, GLenum type) const {
    GLuint shader = glCreateShader(type);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(shader, 1, theCode, codeLength);
    glCompileShader(shader);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(!result) {
        glGetShaderInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        printf("Error Compiling The %d Shader: '%s'\n", type, eLog);
        return;
    }

    glAttachShader(shaderID, shader);
}

void Shader::attach() const {
    glUseProgram(shaderID);
}

GLuint Shader::getUniformLocation(const char* loc) const {
    return glGetUniformLocation(shaderID, loc);
}

Shader::~Shader() {
    if(shaderID != 0) {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }
}

std::string Shader::readFile(const std::string& fileLocation) {
    std::string content;
    std::ifstream fileStream(std::string(INSTALL_PREFIX) + "/resources/shaders/" + fileLocation, std::ios::in);

    if(!fileStream.is_open()) {
        printf("Failed to Read %s! File dosen't exist.\n", fileLocation.c_str());
        return "";
    }

    std::string line;
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}



