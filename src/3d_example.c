#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include "opengl_helpers.c"


float cubeVertices[] = {
    // Positions         // Colors         // Texture Coords
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // 0
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // 1
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // 2
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f, // 3
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   0.0f, 0.0f, // 4
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,   1.0f, 0.0f, // 5
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // 6
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,   0.0f, 1.0f  // 7
};

unsigned int cubeIndices[] = {
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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
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




    //load textures
    GLuint texture1 = createTexture("assets/brick.png");


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
        glm_rotate(cubeModel, spin, (vec3){0.5f, 1.0f, 0.0f});

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
