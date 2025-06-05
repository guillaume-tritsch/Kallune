#include "entity.hpp"
#include <cmath>

Entity::Entity(float startX, float startY) : x(startX), y(startY) {}

void Entity::setFlowField(const FlowField *field)
{
    flowField = field;
}

float Entity::getX() const { return x; }
float Entity::getY() const { return y; }

int Entity::getTileX() const { return static_cast<int>(x / tileSize); }
int Entity::getTileY() const { return static_cast<int>(y / tileSize); }

bool Entity::isAlive() const
{
    return health > 0.0f;
}

bool Entity::isAggressive() const
{
    return aggressive();
}

bool Entity::isCoward() const
{
    return coward();
}

void Entity::takeDamage(float dmg)
{
    health -= dmg;
    if (health < 0.0f)
        health = 0.0f;
}

void Entity::setPlayer(const Player* p) {
    player = p;
}

void Entity::setPosition(float newX, float newY) {
        x = newX;
        y = newY;
    }

EntityType Entity::getType() const {
    return type;
}