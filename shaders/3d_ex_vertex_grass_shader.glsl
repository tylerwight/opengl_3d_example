#version 330 core

layout (location = 0) in vec3 aPos;          // Vertex position
layout (location = 1) in vec3 aColor;        // Vertex color
layout (location = 2) in vec2 aTexCoord;     // Texture coordinates
layout (location = 3) in vec3 aInstanceOffset; // Instance position offset

out vec3 vertexColor;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

void main() {
    // create sway offset
    float swayStrength = aPos.y; // 0 at base, 1 at top
    float sway = sin(time + aInstanceOffset.x * 5.0 + aInstanceOffset.z * 5.0) * 0.1 * swayStrength;

    // Apply sway to vertex position directly
    vec3 modifiedPos = aPos;
    modifiedPos.x += sway; // Apply sway only to the X-axis

    // Compute final world position
    vec4 worldPos = model * vec4(modifiedPos, 1.0);

    // Translate instance position
    worldPos.xyz += aInstanceOffset; // Move to correct plane position

    // Compute final position
    gl_Position = projection * view * worldPos;

    vertexColor = aColor; // Pass color to fragment shader
    texCoord = aTexCoord; // Pass texture coordinates
}
