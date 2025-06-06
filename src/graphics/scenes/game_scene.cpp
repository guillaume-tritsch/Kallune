#include "game_scene.hpp"
#include <tuple>
#include <stb_image.h>
#include "../elements/sprite.hpp"
#include "../elements/animatedSprite.hpp"
#include <iomanip>
#include <sstream>

GLBI_Engine GameEngine;

std::vector<Sprite *> tileset;

AnimatedSprite *badger{};
AnimatedSprite *boar{};
AnimatedSprite *stag{};
AnimatedSprite *wolf{};

GameScene::GameScene()
{

	for (int i = 0; i < 114; ++i)
	{
		std::ostringstream ss;
		ss << "tileset/tile_" << std::setw(3) << std::setfill('0') << i << ".png";
		tileset.push_back(new Sprite(ss.str(), 1.0f, 1.0f));
	}

	badger = new AnimatedSprite("critters/badger/critter_badger_SE_walk.png", 2.7f, 2.7f, 9, 1, 15);
	boar = new AnimatedSprite("critters/boar/boar_SE_run_sheet.png", 3.0f, 2.3f, 2, 2, 10);
	stag = new AnimatedSprite("critters/stag/critter_stag_SE_walk.png", 2.7f, 2.7f, 11, 1, 15);
	wolf = new AnimatedSprite("critters/wolf/wolf-run.png", 4.0f, 4.0f, 8, 4, 15);
}

void GameScene::draw(double deltaTime, Game game)
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

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	GameEngine.mvMatrixStack.pushMatrix();
	GameEngine.mvMatrixStack.addHomothety(Vector3D(1.0f, 1.0f, 1.0f));
	//std::cout << -game.getPlayerX() << "x" << game.getPlayerY() << "y" << std::endl;
	float player_x = game.getPlayerX();
	float player_y = game.getPlayerY();
	float iso_x_offset = (-player_x-player_y) * 0.50f;
	float iso_y_offset = (-player_y + player_x) * 0.25f;
	// std::cout << game.getPlayerX() << "x" << game.getPlayerY() << "y" << std::endl;
	GameEngine.mvMatrixStack.addTranslation(Vector3D(50.0f, -25.0f, 0.0f));
	GameEngine.mvMatrixStack.addTranslation(Vector3D(iso_x_offset, iso_y_offset, 0.0f));

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
				tileType = 4;
			}

			else if (carte_inverted[y][x] == MapType::WALL)
			{
				tileType = 2;
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

	// Draw entities

	GameEngine.mvMatrixStack.pushMatrix();
	//GameEngine.mvMatrixStack.addHomothety(Vector3D(0.4f, 0.4f, 0.4f));

	for (const auto &entity : game.getEntitiesInfo())
	{
		GameEngine.mvMatrixStack.pushMatrix();
		float iso_x_entities = (entity.x - entity.y) * 0.50f;
		float iso_y_entities = (entity.x + entity.y) * 0.25f;

		GameEngine.mvMatrixStack.addTranslation(Vector3D(iso_x_entities, iso_y_entities +0.25, 0.0f));
		GameEngine.updateMvMatrix();

		if (entity.type == EntityType::BOAR)
		{
			boar->draw();
		}
		else if (entity.type == EntityType::DEER)
		{
			stag->draw();
		}
		else if (entity.type == EntityType::WOLF)
		{
			wolf->draw();
		}
		GameEngine.mvMatrixStack.popMatrix();
	}
	

	GameEngine.mvMatrixStack.popMatrix();
	GameEngine.mvMatrixStack.popMatrix();



	GameEngine.mvMatrixStack.pushMatrix();
	GameEngine.mvMatrixStack.addHomothety(Vector3D(0.5f, 0.5f, 0.5f));
	GameEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 0.0f));
	// GameEngine.mvMatrixStack.addTranslation(Vector3D(-1.5f, -1.5f, 0.0f));
	GameEngine.updateMvMatrix();
	badger->update(deltaTime);
	badger->draw();
	GameEngine.mvMatrixStack.popMatrix();

}