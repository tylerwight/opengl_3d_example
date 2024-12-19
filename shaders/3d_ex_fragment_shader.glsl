#version 330 core

in vec3 vertexColor;
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D texture1;

void main() {
    fragColor = texture(texture1, texCoord);
    //fragColor = vec4(texCoord, 0.0, 1.0); // Red = U, Green = V

}
