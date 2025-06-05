
#include "input/input.hpp"
#include "logic/game.hpp"
#include "graphics/graphics.hpp"
#include "utils/scene.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Scene currentScene {Scene::Menu};

int main() {
    Game            game {Game()};
    Graphics        graphics {Graphics()};
    Input           input {Input(graphics.window)};

    double lastFrameTime = glfwGetTime();

    while (!graphics.shouldClose()) {

        // Calculate time delta between frames
        double currentFrameTime = glfwGetTime();
        double deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        input.update(currentScene);

        // add a gui class ?

        game.update(deltaTime, input.state);
        graphics.update(game, input.state);
        graphics.render(deltaTime, currentScene, input.state);
    }

    graphics.close();

    return 0;
}