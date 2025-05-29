#pragma once
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "glbasimac/glbi_texture.hpp"
#include "tools/basic_mesh.hpp"
#include <stb_image.h>
#include <string>


class Sprite {
    public:
        Sprite(const std::string& filename, float sizex = 1.0f, float sizez = 1.0f);
        ~Sprite();

        void draw();
        StandardMesh* getMesh();
        glbasimac::GLBI_Texture* getTexture();

    private:
        StandardMesh* mesh;
        glbasimac::GLBI_Texture* texture {};
};