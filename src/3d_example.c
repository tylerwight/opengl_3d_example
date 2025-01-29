#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include "opengl_helpers.c"

#define GRASS_BLADE_COUNT 500

//TODO
//Fix the texture coordinates on the skybox, they need tweaked.



/////////////////
// SKYBOX  VARS////
////////////////

float skyboxVertices[] = {
    // X     Y       Z     R     G      B        U    V
    // Back face
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.66f, 0.75f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   0.34f, 0.75f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   0.34f, 1.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,   0.66f, 1.0f,

    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   0.34f, 0.25f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,   0.66f, 0.25f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   0.66f, 0.5f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,   0.34f, 0.5f,

    // Left face
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 0.5f,
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   0.33f, 0.5f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,   0.33f, 0.75f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 0.75f,
    

    // Right face
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 0.5f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,   0.67f, 0.5f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   0.67f, 0.749f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 0.749f,

    // Bottom face
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   0.34f, 0.25f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,   0.66f, 0.25f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   0.66f, 0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.34f, 0.0f,

    // Top face
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,   0.34f, 0.5f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   0.66f, 0.5f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   0.66f, 0.75f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,   0.34f, 0.75f
     
     
    
};


unsigned int skyboxIndices[] = {
    0, 1, 2, 2, 3, 0,  // Back face
    4, 5, 6, 6, 7, 4,  // Front face
    8, 9, 10, 10, 11, 8,  // Left face
    12, 13, 14, 14, 15, 12,  // Right face
    16, 17, 18, 18, 19, 16,  // Bottom face
    20, 21, 22, 22, 23, 20   // Top face
};



/////////////////
// CUBE VARS////
////////////////

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




/////////////////
// PLANE VARS////
////////////////
//texture size:
// 652 w
// 1662 h

float planeVertices[] = {
    // X     Y       Z     R     G      B        U    V
    // Back face
    -5.0f, -0.5f, -10.0f,  1.0f, 0.0f, 0.0f,   0.05f, 0.48f, // 0
     0.5f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.95f, 0.48f, // 1
     0.5f,  0.1f, -10.0f,  0.0f, 0.0f, 1.0f,   0.95f, 0.5f, // 2
    -5.0f,  0.1f, -10.0f,  1.0f, 1.0f, 0.0f,   0.05f, 0.5f, // 3

    // Front face
    -5.0f, -0.5f,   0.5f,  0.0f, 1.0f, 1.0f,   0.05, 0.48f, // 4
     0.5f, -0.5f,   0.5f,  1.0f, 0.0f, 1.0f,   0.95f, 0.48f, // 5
     0.5f,  0.1f,   0.5f,  1.0f, 1.0f, 1.0f,   0.95f, 0.5f, // 6
    -5.0f,  0.1f,   0.5f,  0.0f, 0.0f, 0.0f,   0.05f, 0.5f, // 7
    //x = 5.5
    //y = 0.6
    //bl = 31, 800 = 0.05, 0.48
    //br = 620, 800 = 0.95, 0.48
    //tr = 620, 830 = 0.95, 0.5
    //tl = 31, 830 = 0.05, 0.5

    // Left face
    -5.0f, -0.5f, -10.0f,  1.0f, 0.0f, 0.0f,   0.0f, 0.98f, // 8
    -5.0f, -0.5f,   0.5f,  0.0f, 1.0f, 1.0f,   0.0f, 0.5f, // 9
    -5.0f,  0.1f,   0.5f,  0.0f, 0.0f, 0.0f,   0.05f, 0.5f, // 11
    -5.0f,  0.1f, -10.0f,  1.0f, 1.0f, 0.0f,   0.05f, 0.98f, // 10
    
    //x = 10
    //y = 0.5
    //bl = 0, 830 = 0.0, 0.5
    //br = 31, 830 = 0.05, 0.5
    //tr = 31, 1632 = 0.05, 0.98
    //tl = 0, 1632 = 0.00, 0.98
    

    // Right face
     0.5f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 0.5f, // 12
     0.5f, -0.5f,   0.5f,  1.0f, 0.0f, 1.0f,   0.0f, 0.98f, // 13
     0.5f,  0.1f,   0.5f,  1.0f, 1.0f, 1.0f,   0.05f, 0.98f, // 14
     0.5f,  0.1f, -10.0f,  0.0f, 0.0f, 1.0f,   0.05f, 0.5f, // 15

    // Bottom face
    -5.0f, -0.5f,   0.5f,  0.0f, 1.0f, 1.0f,   0.05f, 0.0f, // 16
     0.5f, -0.5f,   0.5f,  1.0f, 0.0f, 1.0f,   0.95f, 0.0f, // 17
     0.5f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.05f, 0.48f, // 18
    -5.0f, -0.5f, -10.0f,  1.0f, 0.0f, 0.0f,   0.95f, 0.48f, // 19
    //bl = 31, 0 = 0.05, 0.0
    //br = 620, 0 = 0.95, 0.0
    //tr = 620, 800 = 0.95, 0.48
    //tl = 31, 800 = 0.05, 0.48
    

    // Top face
    -5.0f,  0.1f, -10.0f,  1.0f, 1.0f, 0.0f,   0.05f, 0.5f, // 20
     0.5f,  0.1f, -10.0f,  0.0f, 0.0f, 1.0f,   0.95f, 0.5f, // 21
     0.5f,  0.1f,   0.5f,  1.0f, 1.0f, 1.0f,   0.95f, 0.98f, // 22
    -5.0f,  0.1f,   0.5f,  0.0f, 0.0f, 0.0f,   0.05f, 0.98f // 23
    //x = 5.5
    //y = 9.5
    //bl = 31, 830 = 0.05, 0.5
    //br = 620, 830 = 0.95, 0.5
    //tr = 620, 1632 = 0.95, 0.98
    //tl = 31, 1632 = 0.05, 0.98
};

unsigned int planeIndices[] = {
    // Back face
    0, 1, 2,
    2, 3, 0,
    // Front face
    4, 5, 6,
    6, 7, 4,
    // Left face
    8, 9, 10,
    10, 11, 8,
    // Right face
    12, 13, 14,
    14, 15, 12,
    // Bottom face
    16, 17, 18,
    18, 19, 16,
    // Top face
    20, 21, 22,
    22, 23, 20
};


/////////////////
// GRASS VARS////
////////////////
vec3 grassPositions[GRASS_BLADE_COUNT];

float grassVertices[] = {
    // X     Y     Z      R     G     B    U      V
    -0.05f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f,  // Bottom Left
     0.05f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // Bottom Right
     0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f   // Top Center
};

unsigned int grassIndices[] = {
    0, 1, 2
};


void generateGrassPositions() {
    for (int i = 0; i < GRASS_BLADE_COUNT; i++) {
        float x = ((float)rand() / RAND_MAX) * 5.0f - 5.0f;
        float z = ((float)rand() / RAND_MAX) * 10.0f - 10.0f;
        float y = 0.1f;  // Make the blades start at the plane surface
        grassPositions[i][0] = x;
        grassPositions[i][1] = y;
        grassPositions[i][2] = z;
        //printf("X: %f, Z: %f, Y: %f\n", x, z, y);
    }
}





// MAIN

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
    GLuint basic_shader = createShaderProgram("shaders/3d_ex_vertex_shader.glsl", "shaders/3d_ex_fragment_shader.glsl");
    GLuint grass_shader = createShaderProgram("shaders/3d_ex_vertex_grass_shader.glsl", "shaders/3d_ex_fragment_shader.glsl");
    glUseProgram(basic_shader);
    
    //////////
    // VAOVBO 1 (cube)
    /////////
    GLuint VAO[4];
    GLuint VBO[4];
    GLuint EBO[4];

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
    //VAO VBO 2 (plane)
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



    ///////////
    //VAO VBO 3 (grass)
    //////////

    glGenVertexArrays(1, &VAO[2]);
    glGenBuffers(1, &VBO[2]);
    glGenBuffers(1, &EBO[2]);

    glBindVertexArray(VAO[2]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(grassVertices), grassVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grassIndices), grassIndices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //instancing data to copy grass
    generateGrassPositions();
    GLuint instanceVBO;
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(grassPositions), &grassPositions[0], GL_STATIC_DRAW);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1);  // One position per instance
    glBindVertexArray(0);

    ///////////
    //VAO VBO 4 (skybox)
    //////////

    glGenVertexArrays(1, &VAO[3]);
    glGenBuffers(1, &VBO[3]);
    glGenBuffers(1, &EBO[3]);

    glBindVertexArray(VAO[3]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), skyboxIndices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);





    GLuint texture_brick_cube = createTexture("assets/concrete_cube.png");
    GLuint texture_grass_plane = createTexture("assets/grass_plane.png");
    GLuint texture_grass_blade = createTexture("assets/grass_blade.png");
    GLuint texture_sky_cube = createTexture("assets/sky_cube.png");
    if (texture_brick_cube == 0 || texture_grass_plane == 0) {
        fprintf(stderr, "Error: Texture failed to load.\n");
        return -1;
    }

    //setup mvp

    // Model matrix -- location of each object
    mat4 cubeModel = GLM_MAT4_IDENTITY_INIT;

    mat4 skyboxModel = GLM_MAT4_IDENTITY_INIT;
    glm_scale(skyboxModel, (vec3){100.0f, 100.0f, 100.0f});

    mat4 planeModel = GLM_MAT4_IDENTITY_INIT;
    glm_translate(planeModel, (vec3){-5.0f, 0.0f, 0.0f});

    mat4 grassModel = GLM_MAT4_IDENTITY_INIT;
    glm_translate(grassModel, (vec3){-5.0f, 0.0f, 0.0f});

    // View matrix -- where the camera is located
    mat4 view = GLM_MAT4_IDENTITY_INIT;
    glm_translate(view, (vec3){0.0f, 0.0f, -100.0f}); // set camera some units back in Z from the cube

    // Projection matrix -- project to screen
    mat4 projection;
    glm_perspective(glm_rad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f, projection); // set FOV, Aspect Ratio, and near and far plane on screen



    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    glUseProgram(basic_shader);
    float spin = 0.005;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        // rotate cube
        glm_rotate(cubeModel, spin, (vec3){0.5f, 1.0f, 0.0f});

        processInput(window, cubeModel, view, projection); //WASD/Mouse movement

        // pass MVP to shader as uniforms
        glUniformMatrix4fv(glGetUniformLocation(basic_shader, "model"), 1, GL_FALSE, (const GLfloat *)cubeModel);
        glUniformMatrix4fv(glGetUniformLocation(basic_shader, "view"), 1, GL_FALSE, (const GLfloat *)view);
        glUniformMatrix4fv(glGetUniformLocation(basic_shader, "projection"), 1, GL_FALSE, (const GLfloat *)projection);
        
        glActiveTexture(GL_TEXTURE0); // Activate texture unit 0
        glBindTexture(GL_TEXTURE_2D, texture_brick_cube); // Bind the texture
        glUniform1i(glGetUniformLocation(basic_shader, "texture1"), 0); // Set the sampler uniform to use texture unit 0



        // Draw cube
        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int) * 2)); // Left face indices


        //Draw Plane
        glUniformMatrix4fv(glGetUniformLocation(basic_shader, "model"), 1, GL_FALSE, (const GLfloat *)planeModel);
        glBindVertexArray(VAO[1]);
        glBindTexture(GL_TEXTURE_2D, texture_grass_plane); // Bind the texture
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        

        // Draw skybox
        glUniformMatrix4fv(glGetUniformLocation(basic_shader, "model"), 1, GL_FALSE, (const GLfloat *)skyboxModel);
        glBindTexture(GL_TEXTURE_2D, texture_sky_cube); // Bind the texture
        glBindVertexArray(VAO[3]);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



        //Draw Grass
        glUseProgram(grass_shader);        
        glUniformMatrix4fv(glGetUniformLocation(grass_shader, "view"), 1, GL_FALSE, (const GLfloat *)view);
        glUniformMatrix4fv(glGetUniformLocation(grass_shader, "projection"), 1, GL_FALSE, (const GLfloat *)projection);
        glUniform1f(glGetUniformLocation(grass_shader, "time"), glfwGetTime());
        glUniformMatrix4fv(glGetUniformLocation(grass_shader, "model"), 1, GL_FALSE, (const GLfloat *)grassModel);
        //glDepthMask(GL_FALSE);
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAO[2]);
        glBindTexture(GL_TEXTURE_2D, texture_grass_blade); 
        glDrawElementsInstanced(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0, GRASS_BLADE_COUNT);
        //glDepthMask(GL_TRUE);
        glUseProgram(basic_shader);



        //resize viewport if window size changes
        int window_w;
        int window_h;
        glfwGetWindowSize(window, &window_w, &window_h);
        glViewport(0, 0, window_w, window_h);

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
