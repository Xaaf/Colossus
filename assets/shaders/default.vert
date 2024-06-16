#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 textureCoord;

out vec2 vertTextureCoord;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(pos, 1.0);
    vertTextureCoord = textureCoord;
}