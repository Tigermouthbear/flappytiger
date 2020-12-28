#version 330
in vec2 TexCoord;

out vec4 colour;

uniform sampler2D theTexture;
uniform vec3 textColor;

void main() {
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(theTexture, TexCoord).r);
    colour = vec4(textColor, 1.0) * sampled;
}