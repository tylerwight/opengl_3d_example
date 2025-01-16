#version 330 core

layout (location = 0) in vec3 aPos;          // Vertex position
layout (location = 1) in vec3 aColor;        // Vertex color
layout (location = 2) in vec2 aTexCoord;     // Texture coordinates
layout (location = 3) in vec3 aInstanceOffset; // Instance position offset

out vec3 vertexColor;
out vec2 texCoord;

uniform mat4 view;
uniform mat4 projection;

void main() {
    // Create the model matrix manually with the translation offset
    mat4 model = mat4(1.0);
    model[3] = vec4(aInstanceOffset, 1.0); // Set the translation in the model matrix

    // Final vertex position
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    vertexColor = aColor; // Pass the color to the fragment shader
    texCoord = aTexCoord; // Pass the texture coordinates
}
