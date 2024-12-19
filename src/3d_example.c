#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include "opengl_helpers.c"

//brick_cube.png coords
// w 3070 px
// h 4090 px

//front
//bottom_left = 1020, 1025
//bottom_right = 2043, 1025
//top_left = 1020, 2047
//top_right = 2043, 2047

//top
//bottom_left = 1020, 2047
//bottom_right = 2043, 2047
//top_left = 1020, 3070
//top_left = 2043, 3070

float cubeVertices[] = {
    // X     Y       Z     R     G      B        U    V
    // Back face
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.66f, 0.75f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   0.33f, 0.75f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   0.33f, 1.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,   0.66f, 1.0f,

    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   0.33f, 0.25f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,   0.66f, 0.25f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   0.66f, 0.5f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,   0.33f, 0.5f,

    // Left face
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 0.5f,
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   0.33f, 0.5f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,   0.33f, 0.75f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 0.75f,
    

    // Right face
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 0.5f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,   0.66f, 0.5f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   0.66f, 0.75f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 0.75f,

    // Bottom face
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   0.33f, 0.25f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,   0.66f, 0.25f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   0.66f, 0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.33f, 0.0f,

    // Top face
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,   0.33f, 0.5f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   0.66f, 0.5f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   0.66f, 0.75f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,   0.33f, 0.75f
     
     
    
};


unsigned int cubeIndices[] = {
    0, 1, 2, 2, 3, 0,  // Back face
    4, 5, 6, 6, 7, 4,  // Front face
    8, 9, 10, 10, 11, 8,  // Left face
    12, 13, 14, 14, 15, 12,  // Right face
    16, 17, 18, 18, 19, 16,  // Bottom face
    20, 21, 22, 22, 23, 20   // Top face
};


float planeVertices[] = {
    // Positions         // Colors         // Texture Coords
    -5.0f, -0.5f, -10.0f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // 0
     0.5f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // 1
     0.5f,  0.1f, -10.0f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // 2
    -5.0f,  0.1f, -10.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f, // 3
    -5.0f, -0.5f,   0.5f,  0.0f, 1.0f, 1.0f,   0.0f, 0.0f, // 4
     0.5f, -0.5f,   0.5f,  1.0f, 0.0f, 1.0f,   1.0f, 0.0f, // 5
     0.5f,  0.1f,   0.5f,  1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // 6
    -5.0f,  0.1f,   0.5f,  0.0f, 0.0f, 0.0f,   0.0f, 1.0f  // 7
};

unsigned int planeIndices[] = {
    // Back face
    0, 1, 2,
    2, 3, 0,
    // Front face
    4, 5, 6,
    6, 7, 4,
    // Left face
    4, 0, 3,
    3, 7, 4,
    // Right face
    1, 5, 6,
    6, 2, 1,
    // Bottom face
    4, 5, 1,
    1, 0, 4,
    // Top face
    3, 2, 6,
    6, 7, 3
};


GLuint createTexture(const char *filePath) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture wrapping and filtering options
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrap vertically
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrap horizontally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
    printf("Texture dimensions: %d x %d, channels: %d\n", width, height, nrChannels);
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

    //load shaders
    GLuint shaderProgram = createShaderProgram("shaders/3d_ex_vertex_shader.glsl", "shaders/3d_ex_fragment_shader.glsl");
    glUseProgram(shaderProgram);
    
    //////////
    // VAOVBO 1
    /////////
    GLuint VAO[2];
    GLuint VBO[2];
    GLuint EBO[2];

    glGenVertexArrays(1, &VAO[0]);
    glGenBuffers(1, &VBO[0]);
    glGenBuffers(1, &EBO[0]);

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);



    ///////////
    //VAO VBO 2
    //////////
    glGenVertexArrays(1, &VAO[1]);
    glGenBuffers(1, &VBO[1]);
    glGenBuffers(1, &EBO[1]);

    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeIndices), planeIndices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);






    GLuint texture1 = createTexture("assets/brick_cube.png");
    if (texture1 == 0) {
        fprintf(stderr, "Error: Texture failed to load.\n");
        return -1;
    }

    //setup mvp

    // Model matrix
    mat4 cubeModel = GLM_MAT4_IDENTITY_INIT;

    mat4 planeModel = GLM_MAT4_IDENTITY_INIT;
    glm_translate(planeModel, (vec3){-5.0f, 0.0f, 0.0f});

    // View matrix
    mat4 view = GLM_MAT4_IDENTITY_INIT;
    glm_translate(view, (vec3){0.0f, 0.0f, -100.0f}); // set camera some units back in Z from the cube

    // Projection matrix
    mat4 projection;
    glm_perspective(glm_rad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f, projection); // set FOV, Aspect Ratio, and near and far plane on screen



    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    glUseProgram(shaderProgram);
    float spin = 0.005;
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        // rotate cube
        //glm_rotate(cubeModel, spin, (vec3){0.5f, 1.0f, 0.0f});

        processInput(window, cubeModel, view, projection);

        // pass MVP to shader as uniforms
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, (const GLfloat *)cubeModel);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, (const GLfloat *)view);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, (const GLfloat *)projection);
        
        glActiveTexture(GL_TEXTURE0); // Activate texture unit 0
        glBindTexture(GL_TEXTURE_2D, texture1); // Bind the texture
        glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0); // Set the sampler uniform to use texture unit 0



        // Draw cube
        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int) * 2)); // Left face indices


        //Draw Plane
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, (const GLfloat *)planeModel);
        glBindVertexArray(VAO[1]);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        
        
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
