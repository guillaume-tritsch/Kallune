#include "draw_scene.hpp"
#include <tuple>
#include <stb_image.h>
#include "graphics/sprite.hpp"
#include <iomanip>
#include <sstream>

GLBI_Engine myEngine;

std::vector<Sprite *> tileset;
const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 10;

int map[MAP_HEIGHT][MAP_WIDTH];

void generateMap()
{
	std::srand(std::time(nullptr));
	for (int y = 0; y < MAP_HEIGHT; ++y)
	{
		for (int x = 0; x < MAP_WIDTH; ++x)
		{
			map[y][x] = rand() % 2;
		}
	}
}

void initScene()
{
	for (int i = 0; i < 114; ++i)
	{
		std::ostringstream ss;
		ss << "tileset/tile_" << std::setw(3) << std::setfill('0') << i << ".png";
		tileset.push_back(new Sprite(ss.str(), 0.2f, 0.2f));
	}

	generateMap();
}

void drawScene()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	// glDepthFunc(GL_LEQUAL);

	myEngine.activateTexturing(true);
	// float z_index = 0.0f;
	for (int layer = MAP_WIDTH + MAP_HEIGHT - 2; layer >= 0; --layer)
	{
		int start_x = std::max(0, layer - MAP_HEIGHT + 1);
		int end_x = std::min(MAP_WIDTH - 1, layer);

		for (int x = start_x; x <= end_x; ++x)
		{
			int y = layer - x;
			if (y < 0 || y >= MAP_HEIGHT)
				continue;

			int tileType = (map[y][x] == 0) ? 0 : 11;

			float iso_x = (x - y) * 0.22f;
			float iso_y = (x + y) * 0.115f;

			myEngine.mvMatrixStack.pushMatrix();
			myEngine.mvMatrixStack.addTranslation(Vector3D(iso_x, iso_y, 0.0f));
			myEngine.updateMvMatrix();

			if (tileType == 0)
			{
				// Tuile de base
				tileset[tileType]->draw();

				// Tuile empilée au-dessus
				myEngine.mvMatrixStack.pushMatrix();
				myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.115f, 0.0f)); // montée d'une "hauteur"
				myEngine.updateMvMatrix();
				tileset[tileType]->draw();
				myEngine.mvMatrixStack.popMatrix();
			}
			else
			{
				tileset[tileType]->draw();
			}

			myEngine.mvMatrixStack.popMatrix();
		}
	}
}