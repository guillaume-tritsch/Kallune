#include "input.hpp"

std::array<int, GLFW_KEY_LAST> keyStates;
bool cursorClicked = false;
double cursorClickTime = 0.0;
double mouseX, mouseY;

void Input::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    keyStates[key] = action;
}

void Input::mouseCallback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        cursorClicked = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        cursorClicked = false;
        cursorClickTime = glfwGetTime();
    }
}

void Input::update() {
    /*Get the mouse position*/
    glfwGetCursorPos(window, &mouseX, &mouseY);

    /* Poll for and process events */
    glfwPollEvents();
}

Input::Input(GLFWwindow* window) {
    this->window = window;
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseCallback);
}