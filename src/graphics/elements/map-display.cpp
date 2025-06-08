#include "map-display.hpp"
#include <iomanip>

MapDisplay::MapDisplay()
{
	for (int i = 0; i < 114; ++i)
	{
		std::ostringstream ss;
		ss << "tileset/tile_" << std::setw(3) << std::setfill('0') << i << ".png";
		tileset.push_back(new Sprite(ss.str(), 1.0f, 1.0f));
	}
}

void MapDisplay::update() {
   
}

void MapDisplay::draw(double deltaTime, Game game)
{
    int MAP_WIDTH = game.map.getWidth();
	int MAP_HEIGHT = game.map.getHeight();

	const std::vector<std::vector<MapType>> &carte = game.map.getMap();
	std::vector<std::vector<MapType>> carte_inverted;
	// invert rows
	for (size_t i = 0; i < 100; i++)
	{
		carte_inverted.push_back(carte[99 - i]);
	}

	int nbr_fleurs = 0;

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

			int tileType;

			if (carte_inverted[y][x] == MapType::WATER)
			{
				tileType = 92;
			}
			else if (carte_inverted[y][x] == MapType::GRASS)
			{
				tileType = 23;
			}
			else if (carte_inverted[y][x] == MapType::SAND)
			{
				tileType = 66;
			}
			else if (carte_inverted[y][x] == MapType::FLOWER)
			{
				nbr_fleurs++;
				tileType = 4;
			}

			else if (carte_inverted[y][x] == MapType::WALL)
			{
				tileType = 2;
			}
			else if (carte_inverted[y][x] == MapType::SOLID_WALL)
			{
				tileType = 12;
			}
			else
			{
				tileType = 3;
			}

			float iso_x = (x - y) * 0.50f;
			float iso_y = (x + y) * 0.25f;

			GameEngine.mvMatrixStack.pushMatrix();
			GameEngine.mvMatrixStack.addTranslation(Vector3D(iso_x, iso_y, 0.0f));
			GameEngine.updateMvMatrix();

			tileset[tileType]->draw();

			GameEngine.mvMatrixStack.popMatrix();
			if (carte_inverted[y][x] == MapType::WALL)
			{
				GameEngine.mvMatrixStack.pushMatrix();
				GameEngine.mvMatrixStack.addTranslation(Vector3D(iso_x, iso_y +0.25f, 0.0f));
				GameEngine.updateMvMatrix();

				tileset[tileType]->draw();

				GameEngine.mvMatrixStack.popMatrix();
			}
			else if (carte_inverted[y][x] == MapType::SOLID_WALL)
			{
				GameEngine.mvMatrixStack.pushMatrix();
				GameEngine.mvMatrixStack.addTranslation(Vector3D(iso_x, iso_y +0.25f, 0.0f));
				GameEngine.updateMvMatrix();

				tileset[tileType]->draw();

				GameEngine.mvMatrixStack.popMatrix();
			}
			else if (carte_inverted[y][x] == MapType::FLOWER)
			{
				GameEngine.mvMatrixStack.pushMatrix();
				GameEngine.mvMatrixStack.addTranslation(Vector3D(iso_x, iso_y + 0.25f, 0.0f));
				GameEngine.updateMvMatrix();

				tileset[44]->draw();

				GameEngine.mvMatrixStack.popMatrix();
			}
		}
    }
}