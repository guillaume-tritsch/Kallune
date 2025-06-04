#define GLFW_INCLUDE_NONE
#include "tools/matrix_stack.hpp"
#include <iostream>
#include <cmath>
#include "graphics.hpp"

/* Window size */

int WINDOW_WIDTH = 1080;
int WINDOW_HEIGHT = 720;


//cursor settings
bool cursorClicked = false;
double cursorClickTime = 0.0;
const double CURSOR_ANIMATION_DURATION = 0.5;

double mouseX, mouseY;
double x_world, y_world;

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

float viewWidth = GL_VIEW_SIZE;
float viewHeight = GL_VIEW_SIZE;



void onWindowResized(GLFWwindow *, int width, int height)
{
    std::cout << "Window resized to " << width << "x" << height << std::endl;
    
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
    
    aspectRatio = width / (float)height;
    glViewport(0, 0, width, height);

    if (aspectRatio > 1.0f)
    {
        viewWidth = GL_VIEW_SIZE * aspectRatio;
        viewHeight = GL_VIEW_SIZE;
    }
    else
    {
        viewWidth = GL_VIEW_SIZE;
        viewHeight = GL_VIEW_SIZE / aspectRatio;
    }

    myEngine.set2DProjection(
        -viewWidth / 2.0f, viewWidth / 2.0f,
        -viewHeight / 2.0f, viewHeight / 2.0f);
}

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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
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


Graphics::Graphics()
{
    // Set error callback
    glfwSetErrorCallback([](int, const char *desc)
                         {
        std::cerr << "GLFW Error: " << desc << "\n";
        std::exit( EXIT_FAILURE ); });

    // Initialize the library
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Callback to a function if an error is rised by GLFW */
    glfwSetErrorCallback(onError);

    // Create a windowed mode window and its OpenGL context
    this->window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Kallune", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLFW Window");
    }

    // -- Callbacks --
    glfwSetWindowSizeCallback(window, onWindowResized);
    glfwSetMouseButtonCallback(window, mouse_button_callback);


    // Make the window's context current
    glfwMakeContextCurrent(window);

    // glfwSetWindowAspectRatio(window, 16, 9);

    // Intialize glad (loads the OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize Glad");
    }

    // Initialize Rendering Engine

    myEngine.mode2D = true;

    myEngine.initGL();

    onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    glfwSetKeyCallback(window, key_callback);

    game_scene = new GameScene();
    menu_scene = new MenuScene();
}

void Graphics::render(Scene currentScene)
{
    /* Get time (in second) at loop beginning */
    double startTime = glfwGetTime();

    /*Get the mouse position*/
    glfwGetCursorPos(window, &mouseX, &mouseY);

    x_world = (mouseX / WINDOW_WIDTH) * viewWidth - viewWidth / 2.0f;
    y_world = (1.0 - mouseY / WINDOW_HEIGHT) * viewHeight - viewHeight / 2.0f;

    // Hide the cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);


    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    switch (currentScene)
    {
    case Scene::Menu:
        menu_scene->draw();
        break;
    case Scene::Playing:
        game_scene->draw();
        break;
    case Scene::GameOver:
        // gameover_scene::drawScene();
        break;
    }

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

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

void Graphics::update(Game game)
{
}

bool Graphics::shouldClose()
{
    return glfwWindowShouldClose(window);
}

void Graphics::close()
{
    glfwTerminate();
}