#include <iostream>
#include <string>
#include <array>

using std::string;
using std::array;

#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "../include/io.h"
#include "../include/shader_program.h"
#include "../include/camera.h"

camera::Camera cameraObj{};

float deltaTime{0.0f};
float lastFrame{0.0f};

float lastX = 400;
float lastY = 300;

bool firstEnter = true;

void framebuffer_resize_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processMouse([[maybe_unused]] GLFWwindow *window, double xPos, double yPos) {
    if (firstEnter) {
        lastX = (float) xPos;
        lastY = (float) yPos;
        firstEnter = false;
    }

    float xOffset = (float) xPos - lastX;
    float yOffset = lastY - (float) yPos; // reversed: y ranges bottom to top
    lastX = (float) xPos;
    lastY = (float) yPos;

    cameraObj.rotate(yOffset, xOffset);
}

void processInput(GLFWwindow *window) {
    float currentFrame{(float) glfwGetTime()};
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraObj.move(camera::Direction::Forward, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraObj.move(camera::Direction::Backward, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraObj.move(camera::Direction::Right, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraObj.move(camera::Direction::Left, deltaTime);
    }
}

int main() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    std::cout << "Successfully initialized GLFW" << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Cube lighting renderer", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create a window" << std::endl;
        glfwTerminate();

        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to setup GLAD" << std::endl;
        glfwTerminate();

        return -1;
    }

    glViewport(0, 0, 800, 600);

    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, processMouse);

    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

    float cubeVertices[]{
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    };

    // Load object cube
    unsigned int objVAO;
    glGenVertexArrays(1, &objVAO);
    glBindVertexArray(objVAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Load light source cube
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // Create shader program for rendering the object
    string vertexShaderSrc = readContent("shaders/obj_vertex_shader.glsl");
    string objFragShaderSrc = readContent("shaders/obj_frag_shader.glsl");
    shader::ShaderProgram objProgram{
            vertexShaderSrc,
            objFragShaderSrc
    };

    // Create shader program for rendering the light source
    string lightSourceVertexShaderSrc = readContent("shaders/light_source_vertex_shader.glsl");
    string lightSourceFragShaderSrc = readContent("shaders/light_source_frag_shader.glsl");
    shader::ShaderProgram lightSourceProgram{
            lightSourceVertexShaderSrc,
            lightSourceFragShaderSrc
    };

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glm::vec3 lightPosition{1.2f, 1.0f, 2.0f};

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::lookAt(cameraObj.getPositionVec(), cameraObj.getTargetVec(), cameraObj.getUpVec());

        // Render object
        objProgram.useProgram();
        glm::mat4 objModel{1.0f};
//        objModel = glm::translate(objModel, glm::vec3{0.0f, 0.0f, -1.0f});
        objProgram.setUniform("model", objModel);
        objProgram.setUniform("view", view);
        objProgram.setUniform("projection", projection);

        objProgram.setUniform("lightColor", array{1.0f, 1.0f, 1.0f});
        objProgram.setUniform("objectColor", array{1.0f, 0.5f, 0.31f});
        objProgram.setUniform("lightPos", array{lightPosition.x, lightPosition.y, lightPosition.z});

        glm::vec3 viewPos = cameraObj.getPositionVec();
        objProgram.setUniform("viewPos", array{viewPos.x, viewPos.y, viewPos.z});

        glBindVertexArray(objVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Render light source
        lightSourceProgram.useProgram();
        glm::mat4 model{1.0f};
        model = glm::translate(model, lightPosition);
        model = glm::scale(model, glm::vec3{0.2f});
        lightSourceProgram.setUniform("model", model);
        lightSourceProgram.setUniform("view", view);
        lightSourceProgram.setUniform("projection", projection);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
