#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "draw_scene.hpp"
#include "tools/matrix_stack.hpp"
#include <iostream>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

/* Window size */

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 800;
double mouseX, mouseY;
double worldX, worldY;

float viewWidth;
float viewHeight;

bool hasWindowBeenFixed = false;

using namespace glbasimac;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;
static float aspectRatio = 1.0f;

/* Error handling function */
void onError(int error, const char *description)
{
    std::cout << "GLFW Error (" << error << ") : " << description << std::endl;
}

static const float GL_VIEW_SIZE = 6.0f;

void onWindowResized(GLFWwindow *, int width, int height)
{
    std::cout << "Window resized to " << width << "x" << height << std::endl;
    aspectRatio = width / (float)height;
    glViewport(0, 0, width, height);

    float viewWidth = GL_VIEW_SIZE;
    float viewHeight = GL_VIEW_SIZE;

    if (aspectRatio > 1.0f)
    {
        viewWidth = GL_VIEW_SIZE * aspectRatio;
    }
    else
    {
        viewHeight = GL_VIEW_SIZE / aspectRatio;
    }

    myEngine.set2DProjection(
        -viewWidth / 2.0f, viewWidth / 2.0f,
        -viewHeight / 2.0f, viewHeight / 2.0f);

    hasWindowBeenFixed = false;
};

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        default:
            break;
        }
    }
}

int main()
{

    // Set error callback
    glfwSetErrorCallback([](int, const char *desc)
                         {
        std::cerr << "GLFW Error: " << desc << "\n";
        std::exit( EXIT_FAILURE ); });

    // Initialize the library
    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Callback to a function if an error is rised by GLFW */
    glfwSetErrorCallback(onError);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Kallune", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // -- Callbacks --
    glfwSetWindowSizeCallback(window, onWindowResized);

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // hide the mouse cursor
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // Intialize glad (loads the OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    // Initialize Rendering Engine

    myEngine.mode2D = true;

    myEngine.initGL();

    onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    glfwSetKeyCallback(window, key_callback);

    initScene();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Get time (in second) at loop beginning */
        double startTime = glfwGetTime();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glfwGetCursorPos(window, &mouseX, &mouseY);
        viewWidth = GL_VIEW_SIZE * (aspectRatio > 1.0f ? aspectRatio : 1.0f);
        viewHeight = GL_VIEW_SIZE / (aspectRatio < 1.0f ? aspectRatio : 1.0f);

        // Conversion pixel écran → coordonnées monde OpenGL
        float worldX = ((float)mouseX / WINDOW_WIDTH) * viewWidth - viewWidth / 2.0f;
        float worldY = ((WINDOW_HEIGHT - (float)mouseY) / WINDOW_HEIGHT) * viewHeight - viewHeight / 2.0f;

        drawScene();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* macOS specific fix */
        if (!hasWindowBeenFixed)
        {
            hasWindowBeenFixed = true;
            glfwSetWindowPos(window, 0, 0);
        }

        /* Poll for and process events */
        glfwPollEvents();

        /* Elapsed time computation from loop begining */
        double elapsedTime = glfwGetTime() - startTime;
        /* If to few time is spend vs our wanted FPS, we wait */
        while (elapsedTime < FRAMERATE_IN_SECONDS)
        {
            glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
            elapsedTime = glfwGetTime() - startTime;
        }
    }

    glfwTerminate();
    return 0;
}

// MAP GENERATION

// void printMap(CellularAutomaton &automaton)
// {
//     vector<vector<int>> *map = automaton.getMap();
//     unsigned int width = automaton.getWidth();
//     unsigned int height = automaton.getHeight();

//     for (unsigned int y = 0; y < height; ++y)
//     {
//         for (unsigned int x = 0; x < width; ++x)
//         {
//             switch ((*map)[x][y])
//             {
//             case 0:
//                 cout << '.';
//                 break;
//             case 1:
//                 cout << '#';
//                 break;
//             default:
//                 cout << (*map)[x][y] ;
//                 break;
//             }
//         }
//         cout << '\n';
//     }
// }

// void print_matrix(const std::vector<std::vector<float>>& matrix) {
//     for (const auto& row : matrix) {
//         for (float value : row) {
//             std::cout << std::setw(8) << std::fixed << std::setprecision(2) << value << " ";
//         }
//         std::cout << '\n';
//     }
// }

// int main()
// {
//     // DiamondSquareMap e(12);
//     // cout << "EEEEEE" << endl;
//     // e.generate();
//     // print_matrix(e.value);

//     // std::cout << std::endl << std::endl << e.size << std::endl;
//     unsigned int width = 100;
//     unsigned int height = 50;

//     CellularAutomaton automaton(width, height);
//     automaton.generate(60, 6, 2, 4, 4);
//     printMap(automaton);

//     return 0;
// }