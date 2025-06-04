#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "glbasimac/glbi_texture.hpp"
#include "tools/basic_mesh.hpp"

#include "graphics/elements/animatedSprite.hpp"

using namespace glbasimac;

/* OpenGL Engine */
extern GLBI_Engine myEngine;
extern double mouseX, mouseY;
extern double x_world;
extern double y_world;
extern bool cursorClicked;
extern double cursorClickTime;

class MenuScene
{
public:
    MenuScene();
    ~MenuScene() = default;

    void draw();

private:
    AnimatedSprite *background{};
    Sprite *cursorSprite{};
    AnimatedSprite *cursorAnimatedSprite{};
};