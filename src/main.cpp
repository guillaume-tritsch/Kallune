#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "graphics/sprite.hpp"

std::string loadFile(const std::string& path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint compileShader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    return shader;
}

GLuint createShaderProgram(const std::string& vsPath, const std::string& fsPath) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, loadFile(vsPath));
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, loadFile(fsPath));
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Simple Sprite", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    GLuint shader = createShaderProgram("sprite.vs", "sprite.fs");
    glUseProgram(shader);
    glUniform1i(glGetUniformLocation(shader, "sprite"), 0); // bind texture unit 0

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    Sprite mySprite("assets/images/sprite.png", 32, 32);
    std::cout << "Sprite created" << std::endl;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        mySprite.draw(200.0f, 150.0f); // draw at x=200, y=150

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
