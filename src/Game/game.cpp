#include "game.h"
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

void Game::update(float deltaTime)
{
    // Recalcul du flowfield vers le joueur (nouvelle position)
    updateFlowField();

    // Mise à jour des entités (décision comportement, déplacement, etc)
    updateEntities(deltaTime);
}

float Game::getPlayerX() const {
    return player.getX();
}

float Game::getPlayerY() const {
    return player.getY();
}

std::vector<Game::EntityInfo> Game::getEntitiesInfo() const {
    std::vector<EntityInfo> infos;
    for (const auto& e : entities) {
        infos.push_back(EntityInfo{
            e->getX(),
            e->getY(),
            e->isAlive(),
            e->isAgressive()
        });
    }
    return infos;
}

void Game::onKeyDown(int keyCode) {
    keyStates[keyCode] = true;
}

void Game::onKeyUp(int keyCode) {
    keyStates[keyCode] = false;
}

bool Game::isKeyPressed(int keyCode) const {
    auto it = keyStates.find(keyCode);
    return it != keyStates.end() && it->second;
}

void Game::generateEntities(int countWolf, int countBoar, int countDeer) {
    // Génère les entités, place aléatoirement sur des cases praticables
    for (int i = 0; i < countWolf; ++i) {
        auto wolf = std::make_unique<Wolf>(0, 0, &player, &flowField);
        placeEntityRandomly(wolf.get());
        entities.push_back(std::move(wolf));
    }
    for (int i = 0; i < countBoar; ++i) {
        auto boar = std::make_unique<Boar>(0, 0, &player, &flowField);
        placeEntityRandomly(boar.get());
        entities.push_back(std::move(boar));
    }
    for (int i = 0; i < countDeer; ++i) {
        auto deer = std::make_unique<Deer>(0, 0, &player, &flowField);
        placeEntityRandomly(deer.get());
        entities.push_back(std::move(deer));
    }
}

void Game::placeEntityRandomly(Entity* entity) {
    int w = map.getWidth();
    int h = map.getHeight();

    int tries = 0;
    const int maxTries = 100;

    while (tries < maxTries) {
        int x = std::rand() % w;
        int y = std::rand() % h;
        if (isWalkableTile(x, y)) {
            // Positionner entité au centre de la case
            entity->setPosition(x + 0.5f, y + 0.5f);
            return;
        }
        ++tries;
    }
    // Si pas trouvé de place, positionne au centre map par défaut
    entity->setPosition(w / 2.0f, h / 2.0f);
}

bool Game::isWalkableTile(int x, int y) const {
    if (x < 0 || y < 0 || x >= map.getWidth() || y >= map.getHeight())
        return false;
    // Exclure murs / eau (vitesse 0)
    float speed = map.getSpeedMap()[x][y];
    return speed > 0.0f;
}

void Game::updateFlowField() {
    int px = static_cast<int>(player.getX());
    int py = static_cast<int>(player.getY());
    flowField.computeFlowField(px, py, map);
}

void Game::updateEntities(float deltaTime) {
    for (auto& entity : entities) {
        entity->decideBehavior(player);
        entity->update(deltaTime);
    }
}
