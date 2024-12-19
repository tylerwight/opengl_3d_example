#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"


// float cubeVertices[] = {
//     // Positions         // Colors
//     //X    //Y    //Z      //R  //G   //B

//     // plane 1
//     -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
//      0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
//      0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
//      0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
//     -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
//     -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    
//     // plane 2
//     -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
//      0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
//      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
//      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
//     -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
//     -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,

//     // plane 3
//     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
//     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
//     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
//     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
//     -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
//     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

//     // plane 4
//      0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
//      0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
//      0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
//      0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
//      0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
//      0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,

//     // plane 5
//     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
//      0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
//      0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
//      0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
//     -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
//     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,

//     // plane 6
//     -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
//      0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
//      0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
//      0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
//     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
//     -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f
// };

float cubeVertices[] = {
    // Positions         // Colors         // Texture Coords
    //X    //Y    //Z      //R  //G   //B      //U   //V

    // plane 1 (back face)
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    
    // plane 2 (front face)
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   0.0f, 0.0f,

    // plane 3 (left face)
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,

    // plane 4 (right face)
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,   1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   1.0f, 0.0f,

    // plane 5 (bottom face)
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,

    // plane 6 (top face)
    -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,   0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,   0.0f, 0.0f
};



float planeVertices[] = {
    // Positions         // Colors         // Texture Coords
    //X    //Y    //Z      //R  //G   //B      //U   //V

    // plane 1 back
    -5.0f, -0.5f, -10.0f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     0.5f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
     0.5f,  0.1f, -10.0f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.1f, -10.0f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    -5.0f,  0.1f, -10.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
    -5.0f, -0.5f, -10.0f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    
    // plane 2 front
    -5.0f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.1f,  0.5f,  1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.1f,  0.5f,  1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
    -5.0f,  0.1f,  0.5f,  0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
    -5.0f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   0.0f, 0.0f,

    // plane 3 side
    -5.0f,  0.1f,  0.5f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    -5.0f,  0.1f, -10.0f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
    -5.0f, -0.5f, -10.0f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
    -5.0f, -0.5f, -10.0f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
    -5.0f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 0.0f,
    -5.0f,  0.1f,  0.5f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,

    // plane 4 side
     0.5f,  0.1f,  0.5f,  0.0f, 1.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.1f, -10.0f,  1.0f, 0.0f, 1.0f,   1.0f, 1.0f,
     0.5f, -0.5f, -10.0f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
     0.5f, -0.5f, -10.0f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     0.5f,  0.1f,  0.5f,  0.0f, 1.0f, 1.0f,   1.0f, 0.0f,

    // plane 5 bottom
    -5.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
     0.5f, -0.5f, -10.0f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    -5.0f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
    -5.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,

    // plane 6 top 
    -5.0f,  0.1f, -10.0f,  1.0f, 0.0f, 1.0f,   0.0f, 0.0f,
     0.5f,  0.1f, -10.0f,  1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.1f,  0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
     0.5f,  0.1f,  0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
    -5.0f,  0.1f,  0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
    -5.0f,  0.1f, -10.0f,  1.0f, 0.0f, 1.0f,   0.0f, 0.0f
};



// shaders
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n" // Texture coordinate input
"out vec3 vertexColor;\n"
"out vec2 texCoord;\n" // Pass texture coordinates to the fragment shader
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main() {\n"
"    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
"    vertexColor = aColor;\n"
"    texCoord = aTexCoord;\n" // Pass the texture coordinates
"}\n";


const char *fragmentShaderSource = "#version 330 core\n"
"in vec3 vertexColor;\n"
"in vec2 texCoord;\n" // Receive texture coordinates from the vertex shader
"out vec4 fragColor;\n"
"uniform sampler2D texture1;\n"
"void main() {\n"
"    fragColor = texture(texture1, texCoord);\n" // Sample the texture using texCoord
"}\n";


// void processInput(GLFWwindow *window, mat4 *model, mat4 *view, mat4 *projection) {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, 1);
// }

void processInput(GLFWwindow *window, mat4 *model, mat4 *view, mat4 *projection) {
    static vec3 cameraPos = {-2.0f, 0.0f, 10.0f};  // Initial camera position
    static vec3 cameraFront = {0.0f, 0.0f, -1.0f}; // Camera forward direction
    static vec3 cameraUp = {0.0f, 1.0f, 0.0f};    // Camera up direction

    static float yaw = -90.0f;  // Initial yaw (pointing along -Z)
    static float pitch = 0.0f;  // Initial pitch
    static float lastX = 400.0f; // Last mouse X position (assume 800x600 window)
    static float lastY = 300.0f; // Last mouse Y position
    static int firstMouse = 1;  // To handle first mouse movement

    float cameraSpeed = 0.025f;   // Adjust for movement speed
    float mouseSensitivity = 0.2f;  // Adjust for mouse sensitivity

    // Handle ESC key
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);

    // WASD input for movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        vec3 scaledFront;
        glm_vec3_scale(cameraFront, cameraSpeed, scaledFront);
        glm_vec3_add(cameraPos, scaledFront, cameraPos);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        vec3 scaledFront;
        glm_vec3_scale(cameraFront, cameraSpeed, scaledFront);
        glm_vec3_sub(cameraPos, scaledFront, cameraPos);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        vec3 cameraRight;
        glm_vec3_cross(cameraFront, cameraUp, cameraRight);
        glm_vec3_normalize(cameraRight);
        glm_vec3_scale(cameraRight, cameraSpeed, cameraRight);
        glm_vec3_sub(cameraPos, cameraRight, cameraPos);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        vec3 cameraRight;
        glm_vec3_cross(cameraFront, cameraUp, cameraRight);
        glm_vec3_normalize(cameraRight);
        glm_vec3_scale(cameraRight, cameraSpeed, cameraRight);
        glm_vec3_add(cameraPos, cameraRight, cameraPos);
    }

    // Mouse input for camera direction
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = 0;
    }

    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;  // Reversed since Y-coordinates range bottom to top
    lastX = xpos;
    lastY = ypos;

    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    // Constrain the pitch angle to prevent flipping
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // Update camera front vector based on yaw and pitch
    vec3 front;
    front[0] = cosf(glm_rad(yaw)) * cosf(glm_rad(pitch));
    front[1] = sinf(glm_rad(pitch));
    front[2] = sinf(glm_rad(yaw)) * cosf(glm_rad(pitch));
    glm_vec3_normalize(front);
    glm_vec3_copy(front, cameraFront);

    // Update the view matrix
    glm_lookat(cameraPos, (vec3){cameraPos[0] + cameraFront[0], cameraPos[1] + cameraFront[1], cameraPos[2] + cameraFront[2]}, cameraUp, *view);
}

GLuint createTexture(const char *filePath) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture wrapping and filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrap horizontally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrap vertically
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Minification filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Magnification filter

    // Load image using stb_image
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1); // Flip images vertically (most image formats are stored upside down for OpenGL)
    unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        // Load texture data into OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        fprintf(stderr, "Failed to load texture: %s\n", filePath);
        stbi_image_free(data);
        return 0; // Return 0 for failed texture loading
    }

    stbi_image_free(data);
    return textureID;
}


int main() {
    // Initialize GLFW / GLEW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "3D Cube", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    //compile and link shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);



    // Create VAO and VBO
    GLuint VAO[2];
    GLuint VBO[2];
    glGenVertexArrays(1, &VAO[0]);
    glGenBuffers(1, &VBO[0]);

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    //VAO VBO 2
    glGenVertexArrays(1, &VAO[1]);
    glGenBuffers(1, &VBO[1]);

    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);



    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float spin = 0;

    //load texturse
    GLuint texture1 = createTexture("assets/brick.png");
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Input
        

        // Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use shader program
        glUseProgram(shaderProgram);

        // Model matrix
        mat4 model = GLM_MAT4_IDENTITY_INIT;
        glm_rotate(model, spin, (vec3){0.5f, 1.0f, 0.0f});

        mat4 model2 = GLM_MAT4_IDENTITY_INIT;
        glm_translate(model2, (vec3){-5.0f, 0.0f, 0.0f});
        //glm_rotate(model2, (spin * -1.0f), (vec3){0.5f, 1.0f, 0.0f});

        spin += 0.005;
        //printf("time: %f\n", (float)glfwGetTime());

        // View matrix
        mat4 view = GLM_MAT4_IDENTITY_INIT;
        glm_translate(view, (vec3){0.0f, 0.0f, -100.0f}); // set camera some units back in Z from the cube

        // Projection matrix
        mat4 projection;
        glm_perspective(glm_rad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f, projection); // set FOV, Aspect Ratio, and near and far plane on screen

        processInput(window, model, view, projection);

        // pas MVP to shader as uniforms
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, (const GLfloat *)model);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, (const GLfloat *)view);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, (const GLfloat *)projection);
        
        glActiveTexture(GL_TEXTURE0); // Activate texture unit 0
        glBindTexture(GL_TEXTURE_2D, texture1); // Bind the texture
        glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0); // Set the sampler uniform to use texture unit 0



        // Draw cube
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Draw Plane
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, (const GLfloat *)model2);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO[0]);
    glDeleteBuffers(1, &VBO[0]);

    glfwTerminate();
    return 0;
}
