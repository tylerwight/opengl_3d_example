#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "../include/tinyobj_loader_c.h"
#include <stdio.h>
#include <stdlib.h>
#include <cglm/cglm.h>


typedef struct {
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    size_t indexCount;
} Mesh;


// Helper function to load shader code from file
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

// Helper function to compile a shader
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



void file_reader(void *ctx, const char *filename, int is_mtl, const char *obj_filename, char **data, unsigned long *len) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        *data = NULL;
        *len = 0;
        return;
    }

    fseek(file, 0, SEEK_END);
    unsigned long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size + 1);
    if (!buffer) {
        fprintf(stderr, "Failed to allocate memory for file: %s\n", filename);
        fclose(file);
        *data = NULL;
        *len = 0;
        return;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0'; // Null-terminate the buffer

    fclose(file);

    *data = buffer;
    *len = file_size;
}



Mesh loadOBJ(const char *filename) {
    tinyobj_attrib_t attrib;
    tinyobj_shape_t *shapes = NULL;
    size_t num_shapes;
    tinyobj_material_t *materials = NULL;
    size_t num_materials;

    // Initialize the attrib structure
    tinyobj_attrib_init(&attrib);

    // Parse the OBJ file
    int result = tinyobj_parse_obj(&attrib, &shapes, &num_shapes, &materials, &num_materials,
                                   filename, file_reader, NULL, TINYOBJ_FLAG_TRIANGULATE);
    if (result != TINYOBJ_SUCCESS) {
        fprintf(stderr, "Failed to load OBJ file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Calculate the number of elements
    size_t num_vertices = attrib.num_vertices;
    size_t num_normals = attrib.num_normals;
    size_t num_faces = attrib.num_faces;

    // Allocate buffers
    float *vertices = malloc(num_vertices * 3 * sizeof(float));
    float *normals = (num_normals > 0) ? malloc(num_normals * 3 * sizeof(float)) : NULL;
    unsigned int *indices = malloc(num_faces * 3 * sizeof(unsigned int));

    if (!vertices || !indices || (num_normals > 0 && !normals)) {
        fprintf(stderr, "Failed to allocate memory for buffers.\n");
        exit(EXIT_FAILURE);
    }

    // Extract vertex data
    memcpy(vertices, attrib.vertices, num_vertices * 3 * sizeof(float));

    // Extract normal data (if available)
    if (num_normals > 0) {
        memcpy(normals, attrib.normals, num_normals * 3 * sizeof(float));
    }

    // Extract indices and validate
    size_t index_count = 0;
    size_t face_offset = 0;

    for (size_t i = 0; i < attrib.num_face_num_verts; i++) {
        if (attrib.face_num_verts[i] != 3) {
            fprintf(stderr, "Non-triangulated face encountered in OBJ file.\n");
            exit(EXIT_FAILURE);
        }

        for (size_t j = 0; j < 3; j++) {
            tinyobj_vertex_index_t idx = attrib.faces[face_offset + j];

            if (idx.v_idx < 0 || (size_t)idx.v_idx >= num_vertices) {
                fprintf(stderr, "Invalid vertex index: %d\n", idx.v_idx);
                exit(EXIT_FAILURE);
            }

            indices[index_count++] = (unsigned int)idx.v_idx;
        }

        face_offset += attrib.face_num_verts[i];
    }

    // Create OpenGL buffers
    Mesh mesh;
    glGenVertexArrays(1, &mesh.vao);
    glGenBuffers(1, &mesh.vbo);
    glGenBuffers(1, &mesh.ebo);

    glBindVertexArray(mesh.vao);

    // Load vertex data into GPU
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, num_vertices * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

    // Load index data into GPU
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // Set up vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Load normals (if available)
    GLuint normal_vbo = 0;
    if (num_normals > 0) {
        glGenBuffers(1, &normal_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, normal_vbo);
        glBufferData(GL_ARRAY_BUFFER, num_normals * 3 * sizeof(float), normals, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
    }

    glBindVertexArray(0);

    // Store the number of indices for rendering
    mesh.indexCount = index_count;

    // Free allocated memory
    free(vertices);
    free(normals);
    free(indices);
    tinyobj_attrib_free(&attrib);
    tinyobj_shapes_free(shapes, num_shapes);
    tinyobj_materials_free(materials, num_materials);

    return mesh;
}




void renderMesh(const Mesh *mesh) {
    glBindVertexArray(mesh->vao);
    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    // Set up OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "OBJ Loader", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }


    GLuint shaderProgram = createShaderProgram("shaders/mesh_vertex_shader.glsl", "shaders/mesh_fragment_shader.glsl");
    glUseProgram(shaderProgram);


    mat4 modelMatrix;
    glm_mat4_identity(modelMatrix);  // Initialize to identity matrix
    glm_translate(modelMatrix, (vec3){0.0f, 0.0f, -5.0f}); // Move object back 5 units along Z-axis

    mat4 viewMatrix;
    vec3 cameraPos = {0.0f, 0.0f, 3.0f};
    vec3 cameraTarget = {0.0f, 0.0f, 0.0f};
    vec3 upVector = {0.0f, 1.0f, 0.0f};
    glm_lookat(cameraPos, cameraTarget, upVector, viewMatrix);

    mat4 projectionMatrix;
    glm_perspective(glm_rad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f, projectionMatrix); // FOV, aspect ratio, near, far


    GLint modelLoc = glGetUniformLocation(shaderProgram, "uModel");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "uView");
    GLint projLoc = glGetUniformLocation(shaderProgram, "uProjection");





    
    // Load the OBJ file
    Mesh mesh = loadOBJ("assets/man.obj");

    // Set up rendering loop
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(window, modelMatrix, viewMatrix, projectionMatrix);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat *)modelMatrix);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const GLfloat *)viewMatrix);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, (const GLfloat *)projectionMatrix);
        // Render the loaded mesh
        renderMesh(&mesh);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &mesh.vao);
    glDeleteBuffers(1, &mesh.vbo);
    glDeleteBuffers(1, &mesh.ebo);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
