#pragma once

#include <vector>
#include "../Entity/entity.h"
#include "../Entity/Entities/wolf.hpp"
#include "../Entity/Entities/boar.hpp"
#include "../Entity/Entities/deer.hpp"
#include "../Player/Player.h"
#include "../Flowfield/flowfield.h"

using namespace std;

class EntitiesGenerator
{
public:
    EntitiesGenerator(FlowField* flowField, Player* player);

    void update(float deltaTime);
    void spawnWolf(int x, int y);
    void spawnBoar(int x, int y);
    void spawnDeer(int x, int y);
    const vector<Entity*>& getEntities() const;

private:
    vector<Entity*> entities;
    FlowField* flowField;
    Player* player;
};
