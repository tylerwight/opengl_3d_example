#version 330 core

layout(location = 0) in vec3 aPosition; // Vertex position

uniform mat4 uModel;        // Model transformation matrix
uniform mat4 uView;         // View (camera) transformation matrix
uniform mat4 uProjection;   // Projection matrix

void main() {
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}
