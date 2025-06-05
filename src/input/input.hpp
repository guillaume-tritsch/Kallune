#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <array>

class Input {

private:
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void mouseCallback(GLFWwindow *window, int button, int action, int mods);
    GLFWwindow* window;

public:
    Input(GLFWwindow* window);
    void update();
};