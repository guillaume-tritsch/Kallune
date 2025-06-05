#include "entitiesGenerator.hpp"

EntitiesGenerator::EntitiesGenerator(FlowField *flowField, Player *player)
    : flowField(flowField), player(player)
{
}

void EntitiesGenerator::update(float deltaTime)
{
    for (auto it = entities.begin(); it != entities.end();)
    {
        (*it)->update(deltaTime);

        if (!(*it)->isAlive())
        {
            it = entities.erase(it); // plus besoin de delete
        }
        else
        {
            ++it;
        }
    }
}

void EntitiesGenerator::spawnWolf(int x, int y)
{
    entities.push_back(std::make_unique<Wolf>(x, y, player, flowField));
}

void EntitiesGenerator::spawnBoar(int x, int y)
{
    entities.push_back(std::make_unique<Boar>(x, y, player, flowField));
}

void EntitiesGenerator::spawnDeer(int x, int y)
{
    entities.push_back(std::make_unique<Deer>(x, y, player, flowField));
}

const std::vector<std::unique_ptr<Entity>> &EntitiesGenerator::getEntities() const
{
    return entities;
}
