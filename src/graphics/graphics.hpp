#pragma once
#include "utils/scene.hpp"
#include "../logic/game.hpp"
#include "./scenes/game_scene.hpp"

class Graphics {
public:
    // Constructeur
    Graphics();

    // Destructeur
    ~Graphics() = default;

    // Update game state 
    void update(Game game);

    // Render the current frame
    void render(Scene current_scene);

    // Checks if the user requested to close the window
    bool shouldClose();

    void close();

private:
    GLFWwindow *window {};
    GameScene game_scene {GameScene()};
};