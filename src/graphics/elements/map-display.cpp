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

	const siv::PerlinNoise::seed_type seed = 123456u;

	const siv::PerlinNoise perlin{ seed };
	
	for (int y = 0; y < 100; ++y)
	{
		std::vector<double> noiseMapRow;
		for (int x = 0; x < 100; ++x)
		{
			const double noise = perlin.octave2D_01((x * 0.01), (y * 0.01), 7);
			noiseMapRow.push_back(noise);
		}
		noiseMap.push_back(noiseMapRow);
	}
}

void MapDisplay::update(double deltaTime, Game game) {
	// Update the noise map based on the player's position
	int nx = 100 - game.getPlayerX();
	int ny = game.getPlayerY();
	if (nx >= 0 && nx < static_cast<int>(noiseMap.size()) &&
		ny >= 0 && ny < static_cast<int>(noiseMap[nx].size()))
	{
		noiseMap[nx][ny] -= 1.25 * deltaTime;
	}

	for (const auto &entity : game.getEntitiesInfo())
	{
		int nx = 100 - entity.x;
		int ny = entity.y;
		if (nx >= 0 && nx < static_cast<int>(noiseMap.size()) &&
			ny >= 0 && ny < static_cast<int>(noiseMap[nx].size()))
		{
			noiseMap[nx][ny] -= 1.25 * deltaTime;
		}
	}
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
			const double noise {noiseMap[y][x]};

			if (y < 0 || y >= MAP_HEIGHT)
				continue;

			int tileType;

			if (carte_inverted[y][x] == MapType::WATER)
			{
				tileType = 92;
			}
			else if (carte_inverted[y][x] == MapType::GRASS)
			{
				if(noise > 0.66) {
					tileType = 23;
				} 
				else if (noise > 0.33) {
					tileType = 22;
				}
				else{
					tileType = 24;
				}
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

			const double noise {noiseMap[y][x] / 2};
			int height {};
			if(noise > 0.85) {
				height = 4;
			} 
			else if (noise > 0.5) {
				height = 3;
			}
			else if (noise > 0.25) {
				height = 2;
			} 
			else {
				height = 1;
			}

			GameEngine.mvMatrixStack.popMatrix();
			if (carte_inverted[y][x] == MapType::SOLID_WALL || carte_inverted[y][x] == MapType::WALL)
			{
				for (int i = 0; i < height; ++i)
				{
					GameEngine.mvMatrixStack.pushMatrix();
					GameEngine.mvMatrixStack.addTranslation(Vector3D(iso_x, iso_y + 0.25f * (i + 1), 0.0f));
					GameEngine.updateMvMatrix();

					tileset[tileType]->draw();

					GameEngine.mvMatrixStack.popMatrix();
				}
			}
			else if (carte_inverted[y][x] == MapType::FLOWER)
			{
				GameEngine.mvMatrixStack.pushMatrix();
				GameEngine.mvMatrixStack.addTranslation(Vector3D(iso_x, iso_y + 0.25f, 0.0f));
				GameEngine.updateMvMatrix();

				if(noise > 0.75) {
					tileset[44]->draw();
				} 
				else if (noise > 0.5) {
					tileset[45]->draw();
				}
				else if (noise > 0.25) {
					tileset[46]->draw();
				} 
				else {
					tileset[47]->draw();
				}

				GameEngine.mvMatrixStack.popMatrix();
			}
		}
    }
}