//
// Created by Tigermouthbear on 12/28/20.
//

#include "Texture.h"

Texture::Texture(const std::string& file) {
    this->format = file.substr(file.find_last_of('.')) == ".png" ? PNG : JPG;
    textureID = width = height = bitDepth = 0;
    location = std::string(INSTALL_PREFIX) + "/resources/" + file;
}

Texture::Texture(const std::string& file, Texture::Format format) {
    this->format = format;
    textureID = width = height = bitDepth = 0;
    location = std::string(INSTALL_PREFIX) + "/resources/" + file;
}

bool Texture::load() {
    // load texture from file
    unsigned char* texData = stbi_load(location.c_str(), &width, &height, &bitDepth, 0);

    // if failed to find return false
    if(!texData) {
        printf("Failed to Find: %s\n", location.c_str());
        return false;
    }

    // generate texture program and bind
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // set tex parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // set texture
    int spec = format == PNG ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, spec, width, height, 0, spec, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // free image from memory
    stbi_image_free(texData);

    return true;
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

Texture::~Texture() {
    glDeleteTextures(1, &textureID);
    textureID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    location = "";
}
