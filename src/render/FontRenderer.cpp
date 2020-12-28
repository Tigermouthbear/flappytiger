//
// Created by Tigermouthbear on 12/28/20.
//

#include "FontRenderer.h"

#include <iostream>

FontRenderer::FontRenderer(const std::string& fontLocation) {
    loc = fontLocation;
}

// https://learnopengl.com/code_viewer_gh.php?code=src/7.in_practice/2.text_rendering/text_rendering.cpp
bool FontRenderer::init() {
    FT_Library ft;
    if(FT_Init_FreeType(&ft)) {
        std::cout << "FREETYPE: Failed to load FreeType" << std::endl;
        return false;
    }

    // load font as face
    FT_Face face;
    if(FT_New_Face(ft, loc.c_str(), 0, &face)) {
        std::cout << "FREETYPE: Failed to load font" << std::endl;
        return false;
    } else {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for(unsigned char c = 0; c < 128; c++) {
            // load character glyph
            if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cout << "FREETYTPE: Failed to load Glyph " << c << std::endl;
                continue;
            }

            // generate texture program and bind
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            // set texture
            glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
            );

            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // store for later use
            Glyph glyph = {
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    static_cast<unsigned int>(face->glyph->advance.x)
            };
            glyphMap.insert(std::pair<char, Glyph>(c, glyph));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return true;
}

void FontRenderer::drawString(std::string text, float x, float y, float scale, glm::vec3 color) {
    // enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // attach shader and set uniform color
    shader.attach();
    glUniform3f(uniformColor.getID(), color.x, color.y, color.z);

    // iterate through all characters
    std::string::const_iterator c;
    for(c = text.begin(); c != text.end(); c++) {
        Glyph glyph = glyphMap[*c];

        // calculate points for the glyph
        float xpos = x + glyph.bearing.x * scale;
        float ypos = y - (glyph.size.y - glyph.bearing.y) * scale * 550/700; // multiply by ascpect ratio of viewport
        float w = glyph.size.x * scale;
        float h = glyph.size.y * scale;
        *vertices = {
                xpos, ypos,          0, 0, 1,
                xpos, ypos + h,      0, 0, 0,
                xpos + w, ypos + h,  0, 1, 0,
                xpos + w, ypos,      0, 1, 1,
        };

        // render
        glBindTexture(GL_TEXTURE_2D, glyph.texId);
        mesh.render();

        x += (glyph.advance >> 6) * scale; // advance cursors for next glyph
    }
}

float FontRenderer::getStringWidth(std::string text, float scale) {
    float width = 0;

    // iterate through all characters and add advance
    std::string::const_iterator c;
    for(c = text.begin(); c != text.end(); c++) {
        Glyph glyph = glyphMap[*c];
        width += (glyph.advance >> 6) * scale;
    }

    return width;
}

float FontRenderer::getFontHeight(float scale) {
    return glyphMap['E'].size.y * scale;
}

FontRenderer::~FontRenderer() {
    delete vertices;
}
