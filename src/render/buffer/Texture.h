//
// Created by Tigermouthbear on 12/28/20.
//

#ifndef FLAPPYTIGER_TEXTURE_H
#define FLAPPYTIGER_TEXTURE_H

#include <string>
#include <GL/glew.h>
#include "../stb_image.h"

class Texture {
public:
    enum Format { PNG, JPG };

    Texture(const std::string& file);

    Texture(const std::string& file, Format format);

    bool load();

    void bind();

    ~Texture();

private:
    Format format;
    GLuint textureID;
    int width, height, bitDepth;

    std::string location;
};


#endif //FLAPPYTIGER_TEXTURE_H
