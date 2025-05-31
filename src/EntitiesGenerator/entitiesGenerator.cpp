#include "entitiesGenerator.h"

EntitiesGenerator::EntitiesGenerator(FlowField* flowField, Player* player)
    : flowField(flowField), player(player)
{
}

void EntitiesGenerator::update(float deltaTime)
{
    for (auto it = entities.begin(); it != entities.end();)
    {
        Entity* entity = *it;
        entity->update(deltaTime);

        if (!entity->isAlive())
        {
            delete entity;
            it = entities.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void EntitiesGenerator::spawnWolf(int x, int y)
{
    entities.push_back(new Wolf(x, y, player, flowField));
}

void EntitiesGenerator::spawnBoar(int x, int y)
{
    entities.push_back(new Boar(x, y, player, flowField));
}

void EntitiesGenerator::spawnDeer(int x, int y)
{
    entities.push_back(new Deer(x, y, player, flowField));
}

const vector<Entity*>& EntitiesGenerator::getEntities() const
{
    return entities;
}
