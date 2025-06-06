
#include "input/input.hpp"
#include "logic/game.hpp"
#include "graphics/graphics.hpp"
#include "utils/scene.hpp"
#include "utils/router.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{

    Router router{Router()};
    Game game{Game()};
    Graphics graphics{Graphics()};
    Input input{Input(graphics.window)};

    double lastFrameTime = glfwGetTime();

    while (!graphics.shouldClose())
    {

        // Calculate time delta between frames
        double currentFrameTime = glfwGetTime();
        double deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        input.update(&router);
        if (router.currentScene != Scene::Pause)
        {
            game.update(deltaTime, input.state);
        }
        graphics.update(game, input.state, &router);
        graphics.render(deltaTime, &router, input.state, game);
    }

    graphics.close();

    return 0;
}