#pragma once
#include <vector>
#include "graphics/elements/sprite.hpp"
#include "logic/game.hpp"
#include "utils/map.hpp"
#include "glbasimac/glbi_engine.hpp"

using namespace glbasimac;
extern GLBI_Engine GameEngine;

class MapDisplay
{
public:
    MapDisplay();
    ~MapDisplay() = default;

    void update();
    void draw(double deltaTime, Game game);

private:
    std::vector<Sprite *> tileset;
};