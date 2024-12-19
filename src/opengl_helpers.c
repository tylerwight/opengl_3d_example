#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>



char *loadShaderSource(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        fprintf(stderr, "Failed to open shader file: %s\n", filePath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *source = malloc(length + 1);
    fread(source, 1, length, file);
    source[length] = '\0';
    fclose(file);

    return source;
}

GLuint compileShader(const char *filePath, GLenum shaderType) {
    char *source = loadShaderSource(filePath);
    if (!source) return 0;

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, (const char **)&source, NULL);
    glCompileShader(shader);

    // Check for compilation errors
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        fprintf(stderr, "Shader compilation error (%s): %s\n", filePath, infoLog);
    }

    free(source);
    return shader;
}



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

// Helper function to link shaders into a program
GLuint createShaderProgram(const char *vertexPath, const char *fragmentPath) {
    GLuint vertexShader = compileShader(vertexPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentPath, GL_FRAGMENT_SHADER);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check for linking errors
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        fprintf(stderr, "Program linking error: %s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}



// GLuint createTexture(const char *filePath) {
//     GLuint textureID;
//     glGenTextures(1, &textureID);
//     glBindTexture(GL_TEXTURE_2D, textureID);

//     // Set texture wrapping and filtering options
//     //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrap vertically
//     //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrap horizontally
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Minification filter
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Magnification filter

//     // Load image using stb_image
//     int width, height, nrChannels;
//     stbi_set_flip_vertically_on_load(1); // Flip images vertically (most image formats are stored upside down for OpenGL)
//     unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);
//     if (data) {
//         GLenum format;
//         if (nrChannels == 1)
//             format = GL_RED;
//         else if (nrChannels == 3)
//             format = GL_RGB;
//         else if (nrChannels == 4)
//             format = GL_RGBA;

//         // Load texture data into OpenGL
//         glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     } else {
//         fprintf(stderr, "Failed to load texture: %s\n", filePath);
//         stbi_image_free(data);
//         return 0; // Return 0 for failed texture loading
//     }

//     stbi_image_free(data);
//     return textureID;
// }