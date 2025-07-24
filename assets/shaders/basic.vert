#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTextureCoord;

out vec3 color;
out vec2 textureCoord;

// Separate matrices for proper 3D rendering
uniform mat4 model;       // Model transformation matrix
uniform mat4 view;        // View matrix (camera)
uniform mat4 projection;  // Projection matrix

void main() {
    // Standard MVP (Model-View-Projection) transformation
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    color = aColor;
    textureCoord = aTextureCoord;
}