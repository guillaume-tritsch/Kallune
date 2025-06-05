#include "game.hpp"
#include <cstdlib>
#include <ctime>

Game::Game()
    : map(), flowField(map.getWidth(), map.getHeight()), player(0.0f, 0.0f)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Générer la map (déjà fait dans map constructor)
    // Initialiser player quelque part valide
    player = Player(50.0f, 50.0f); // exemple, ou place selon map

    updateFlowField();
    generateEntities(5, 3, 4);
}

void Game::update(float deltaTime, Input input)
{
    // Recalcul du flowfield vers le joueur (nouvelle position)
    updateFlowField();

    // Mise à jour des entités (décision comportement, déplacement, etc)
    updateEntities(deltaTime);
}

float Game::getPlayerX() const
{
    return player.getX();
}

float Game::getPlayerY() const
{
    return player.getY();
}

// Add this method:
std::vector<EntityInfo> Game::getEntitiesInfo() const
{
    std::vector<EntityInfo> infos;
    infos.reserve(entities.size());
    for (const auto& e : entities) {
        infos.emplace_back(EntityInfo{
            e->getX(),
            e->getY(),
            e->isAlive(),
            e->isAggressive()
        });
    }

    return infos;
}

void Game::onKeyDown(int keyCode)
{
    keyStates[keyCode] = true;
}

void Game::onKeyUp(int keyCode)
{
    keyStates[keyCode] = false;
}

bool Game::isKeyPressed(int keyCode) const
{
    auto it = keyStates.find(keyCode);
    return it != keyStates.end() && it->second;
}

void Game::generateEntities(int countWolf, int countBoar, int countDeer)
{
    // Génère les entités, place aléatoirement sur des cases praticables
    for (int i = 0; i < countWolf; ++i)
    {
        Wolf* wolf = new Wolf(0, 0, &player, &flowField);  // Changed from std::make_unique
        placeEntityRandomly(wolf);
        entities.push_back(wolf);  // No std::move needed
    }
    for (int i = 0; i < countBoar; ++i)
    {
        Boar* boar = new Boar(0, 0, &player, &flowField);  // Changed from std::make_unique
        placeEntityRandomly(boar);
        entities.push_back(boar);  // No std::move needed
    }
    for (int i = 0; i < countDeer; ++i)
    {
        Deer* deer = new Deer(0, 0, &player, &flowField);  // Changed from std::make_unique
        placeEntityRandomly(deer);
        entities.push_back(deer);  // No std::move needed
    }
}

// Add destructor to clean up memory
Game::~Game()
{
    for (auto entity : entities)
    {
        delete entity;
    }
}
void Game::placeEntityRandomly(Entity *entity)
{
    int w = map.getWidth();
    int h = map.getHeight();

    int tries = 0;
    const int maxTries = 100;

    while (tries < maxTries)
    {
        int x = std::rand() % w;
        int y = std::rand() % h;
        if (isWalkableTile(x, y))
        {
            entity->setPosition(x + 0.5f, y + 0.5f);
            return;
        }
        ++tries;
    }
    entity->setPosition(w / 2.0f, h / 2.0f);
}
bool Game::isWalkableTile(int x, int y) const
{
    if (x < 0 || y < 0 || x >= map.getWidth() || y >= map.getHeight())
        return false;
    // Exclure murs / eau (vitesse 0)
    float speed = map.getSpeedMap()[x][y];
    return speed > 0.0f;
}

void Game::updateFlowField()
{
    int px = static_cast<int>(player.getX());
    int py = static_cast<int>(player.getY());
    flowField.computeFlowField(px, py, map);
}

void Game::updateEntities(float deltaTime)
{
    for (auto &entity : entities)
    {
        entity->decideBehavior(player);
        entity->update(deltaTime);
    }
}
