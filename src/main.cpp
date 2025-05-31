#include "GLFW/glfw3.h"
#include "logic/game.hpp"
#include "graphics/graphics.hpp"
#include "interactions/interactions.hpp"
#include "utils/scene.hpp"

Scene currentScene {Scene::Menu};

void setScene(Scene newScene) {
    currentScene = newScene;
}

int main() {
    Game            game {Game()};
    Graphics        graphics {Graphics()};
    Interactions    interactions {Interactions()};

    while (!graphics.shouldClose()) {
        game.update();
        graphics.update(game);
        graphics.render(currentScene);
    }

    glfwTerminate();

    return 0;
}