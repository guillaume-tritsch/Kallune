
#include "input/input.hpp"
// #include "logic/game.hpp"
#include "graphics/graphics.hpp"
#include "utils/scene.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Scene currentScene {Scene::Menu};

void setScene(Scene newScene) {
    currentScene = newScene;
}

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

        input.update();
        game.update(deltaTime, input);
        graphics.update(game);
        graphics.render(deltaTime, currentScene, input);
    }

    graphics.close();

    return 0;
}