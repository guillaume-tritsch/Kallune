#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "glbasimac/glbi_texture.hpp"
#include "tools/basic_mesh.hpp"

using namespace glbasimac;

/* OpenGL Engine */
extern GLBI_Engine myEngine;

void initScene();

void drawFrame();

void drawBase();

void drawArm();

void drawPan();

void drawScene();

