#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "glbasimac/glbi_texture.hpp"
#include "tools/basic_mesh.hpp"
#include "logic/game.hpp"

#include "graphics/elements/sprite.hpp"
#include "input/scenes/playing_state.hpp"
#include "utils/scene.hpp"
#include "utils/router.hpp"

using namespace glbasimac;

/* OpenGL Engine */
extern GLBI_Engine GameEngine;
extern double mouseX, mouseY;
extern double worldX, worldY;

extern int WINDOW_WIDTH, WINDOW_HEIGHT;
extern float viewWidth, viewHeight;

class GameScene
{
public:
    GameScene();
    ~GameScene() = default;
    void draw(double deltaTime, Game game);
    void update(InputState inputState, Router *router);

private:

    Sprite *pauseButton {};
    Sprite *pauseButtonHover {};

    PlayingState state{PlayingState()};
};