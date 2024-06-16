#version 330 core

out vec4 fragColor;

in vec2 vertTextureCoord;

uniform sampler2D textureSampler;

void main() {
    fragColor = texture(textureSampler, vertTextureCoord);
}