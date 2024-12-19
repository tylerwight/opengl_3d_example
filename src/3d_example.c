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
    

    // VAOVBO 1
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


    //load textures
    GLuint texture1 = createTexture("assets/brick.png");


    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
     float spin = 0;
    // Main loop
    while (!glfwWindowShouldClose(window)) {
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
