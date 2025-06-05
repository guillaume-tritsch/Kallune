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
            delete *it;
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

const std::vector<Entity*>& EntitiesGenerator::getEntities() const
{
    return entities;
}

// Add destructor
EntitiesGenerator::~EntitiesGenerator()
{
    for (auto entity : entities)
    {
        delete entity;
    }
}