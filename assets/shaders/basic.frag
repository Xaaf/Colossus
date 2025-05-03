#version 330 core

out vec4 fragColor;

uniform vec4 someColor;

void main() {
    fragColor = someColor;
}