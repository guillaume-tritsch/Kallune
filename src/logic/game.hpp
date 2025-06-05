#pragma once

#include "Map/map.hpp"
#include "Flowfield/flowfield.hpp"
#include "Player/player.hpp"
#include "Entity/entity.hpp"
#include "Entity/Entities/boar.hpp"
#include "Entity/Entities/deer.hpp"
#include "Entity/Entities/wolf.hpp"
#include "utils/state.hpp"

#include <vector>
#include <memory>
#include <unordered_map>

struct EntityInfo
{
    float x, y;
    bool isAlive;
    bool isAggressive;
};

class Game
{
public:
    Game();
    Map map;

    void update(float deltaTime, InputState input);

    // Accès aux infos
    float getPlayerX() const;
    float getPlayerY() const;

    std::vector<EntityInfo> getEntitiesInfo() const;

    void onKeyDown(int keyCode);
    void onKeyUp(int keyCode);

    bool isKeyPressed(int keyCode) const;

private:
    FlowField flowField;
    Player player;

    // std::vector<std::unique_ptr<Entity>> entities;

    // Garde l'état des touches appuyées
    std::unordered_map<int, bool> keyStates;

    void generateEntities(int countWolf, int countBoar, int countDeer);
    void placeEntityRandomly(Entity *entity);

    void updateFlowField();
    void updateEntities(float deltaTime);

    bool isWalkableTile(int x, int y) const;
};
