#include "logic/game.hpp"
#include "graphics/graphics.hpp"
#include "interactions/interactions.hpp"
#include "utils/scene.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Scene currentScene {Scene::GameOver};

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

    graphics.close();

    return 0;
}