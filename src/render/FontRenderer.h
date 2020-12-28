//
// Created by Tigermouthbear on 12/28/20.
//

#ifndef FLAPPYTIGER_FONTRENDERER_H
#define FLAPPYTIGER_FONTRENDERER_H

#include <map>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "freetype/freetype.h"
#include "shader/Shader.h"
#include "shader/Uniform.h"
#include "buffer/StaticMesh.h"
#include "buffer/DynamicMesh.h"
#include <glm/fwd.hpp>
#include <glm/detail/type_vec2.hpp>
#include <GL/glew.h>

class FontRenderer {
private:
    struct Glyph {
        unsigned int texId;
        glm::ivec2   size;
        glm::ivec2   bearing;
        unsigned int advance;
    };
    std::map<GLchar, Glyph> glyphMap;

    std::vector<GLfloat>* vertices = new std::vector<GLfloat>(20);
    DynamicMesh mesh = DynamicMesh(vertices, new std::vector<unsigned int> { 0, 1, 2, 2, 0, 3 });
    Shader shader = Shader("text.vert", "text.frag");
    Uniform uniformColor = Uniform("textColor", &shader);

    std::string loc;

public:
    FontRenderer(const std::string& fontLocation);

    bool init();

    void drawString(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1, 1,1));

    float getStringWidth(std::string text, float scale);

    float getFontHeight(float scale);

    ~FontRenderer();
};


#endif //FLAPPYTIGER_FONTRENDERER_H
