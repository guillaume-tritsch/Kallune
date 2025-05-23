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
    // aspectRatio = width / (float)height;
    // myEngine.set3DProjection(90.0, aspectRatio, Z_NEAR, Z_FAR);
    aspectRatio = width / (float)height;
	glViewport(0, 0, width, height);
	if (aspectRatio > 1.0)
	{
		myEngine.set2DProjection(-GL_VIEW_SIZE * aspectRatio / 2., GL_VIEW_SIZE * aspectRatio / 2., -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
	}
	else
	{
		myEngine.set2DProjection(-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2., -GL_VIEW_SIZE / (2. * aspectRatio), GL_VIEW_SIZE / (2. * aspectRatio));
	}
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
    glfwSetErrorCallback( []( int, const char* desc )
    {
        std::cerr << "GLFW Error: " << desc << "\n";
        std::exit( EXIT_FAILURE );
    } );

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
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLTemplate", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // -- Callbacks --
    glfwSetWindowSizeCallback(window, onWindowResized);

    // Make the window's context current
    glfwMakeContextCurrent(window);

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

        /* Fix camera position */
        // myEngine.mvMatrixStack.loadIdentity();
        // Vector3D pos_camera = Vector3D(dist_zoom * cos(deg2rad(angle_theta)) * cos(deg2rad(angle_phy)),
        //                                dist_zoom * sin(deg2rad(angle_theta)) * cos(deg2rad(angle_phy)),
        //                                dist_zoom * sin(deg2rad(angle_phy)));

        // Vector3D viewed_point = Vector3D(0.0f, 0.0f, 0.0f);
        // Vector3D up_vector = Vector3D(0.0f, 0.0f, 1.0f);
        // Matrix4D view_matrix = Matrix4D::lookAt(pos_camera, viewed_point, up_vector);
        // myEngine.setViewMatrix(view_matrix);
        // myEngine.updateMvMatrix();

        drawScene();

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

    glfwTerminate();
    return 0;
}