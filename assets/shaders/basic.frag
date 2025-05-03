#version 330 core

out vec4 fragColor;

in vec3 color;
in vec2 textureCoord;

uniform sampler2D textureSampler;

void main() {
    fragColor = texture(textureSampler, textureCoord);
}