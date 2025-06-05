#pragma once

#include "Map/map.hpp"
#include "Flowfield/flowfield.hpp"
#include "Player/player.hpp"
#include "Entity/entity.hpp"
#include "Entity/Entities/boar.hpp"
#include "Entity/Entities/deer.hpp"
#include "Entity/Entities/wolf.hpp"
#include "utils/state.hpp"
#include "utils/entityType.hpp"
#include <vector>
#include <memory>
#include <unordered_map>
#include <set>
#include <utility>
#include <optional>


struct EntityInfo
{
    float x, y;
    bool isAlive;
    bool isAggressive;
    EntityType type;
};

class Game
{
public:
    Game();
    ~Game();
    Map map;

    void update(float deltaTime, InputState input);

    float getPlayerX() const;
    float getPlayerY() const;

    std::vector<EntityInfo> getEntitiesInfo() const;
    std::set<std::pair<int, int>> occupiedTiles;

    bool isKeyPressed(int keyCode) const;
std::optional<std::pair<int, int>> getRandomPlacablePosition();
private:
    FlowField flowField;
    Player player;

    std::vector<Entity *> entities;
    void handlePlayerMovement(const InputState& inputState, float deltaTime);

    std::unordered_map<int, bool> keyStates;

    void generateEntities(int countWolf, int countBoar, int countDeer);
    void placeEntityRandomly(Entity *entity);

    void updateFlowField();
    void updateEntities(float deltaTime);

    bool isWalkableTile(int x, int y) const;
};
