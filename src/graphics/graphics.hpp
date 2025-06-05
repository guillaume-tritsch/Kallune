#pragma once

#include "GLFW/glfw3.h"
#include "utils/scene.hpp"
#include "logic/game.hpp"
#include "graphics/scenes/game_scene.hpp"
#include "graphics/scenes/menu_scene.hpp"
#include "graphics/scenes/menu_scene.hpp"
#include "graphics/scenes/end_scene.hpp"
#include "input/input.hpp"

class Graphics {
public:
    // Constructeur
    Graphics();

    // Destructeur
    ~Graphics() = default;

    // Update game state 
    void update(Game game);

    // Render the current frame
    void render(double deltaTime, Scene current_scene, Input input);

    // Checks if the user requested to close the window
    bool shouldClose();

    void close();

    GLFWwindow *window {};

private:
    static void onError(int error, const char *description);

    static void onWindowResized(GLFWwindow *, int width, int height);

    // SCENES
    GameScene *game_scene {};
    MenuScene *menu_scene {};
    EndScene *end_scene {};

    // CURSOR
    const double CURSOR_ANIMATION_DURATION = 0.5;
    Sprite *cursorSprite{};
    AnimatedSprite *cursorAnimatedSprite{};
};