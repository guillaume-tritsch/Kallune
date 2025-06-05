#pragma once

#include <vector>
#include "../Entity/entity.hpp"
#include "../Entity/Entities/wolf.hpp"
#include "../Entity/Entities/boar.hpp"
#include "../Entity/Entities/deer.hpp"
#include "../Player/player.hpp"
#include "../Flowfield/flowfield.hpp"
#include <memory>

using namespace std;

class EntitiesGenerator
{
public:
    EntitiesGenerator(FlowField *flowField, Player *player);
    ~EntitiesGenerator();

    void update(float deltaTime);
    void spawnWolf(int x, int y);
    void spawnBoar(int x, int y);
    void spawnDeer(int x, int y);
    const std::vector<Entity *> &getEntities() const;
private:
    std::vector<Entity *> entities;
    FlowField *flowField;
    Player *player;
};
