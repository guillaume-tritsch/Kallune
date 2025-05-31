#pragma once
#include "../../Player/player.h"
#include "../../Flowfield/flowfield.h"
#include "../entity.h"
#include <cmath>

class Deer : public Entity
{
public:
    Deer(float startX, float startY);
    Deer(float startX, float startY, const Player* player, const FlowField* flowField);

    void update(float deltaTime) override;
    void decideBehavior(const Player& player) override;

private:
    bool aggressive() const override { return false; }
    bool coward() const override { return true; }

    float fleeDistance = 3.0f;
};

// deer.cpp (si séparé)
Deer::Deer(float startX, float startY) : Entity(startX, startY)
{
    speed = 2.0f;
}

Deer::Deer(float startX, float startY, const Player* player, const FlowField* flowField)
    : Entity(startX, startY)
{
    this->player = player;
    this->flowField = flowField;
    speed = 2.0f;
}

void Deer::decideBehavior(const Player& player)
{
    float dx = player.getX() - x;
    float dy = player.getY() - y;
    float distanceSq = dx * dx + dy * dy;

    if (distanceSq < fleeDistance * fleeDistance)
    {
        behavior = BehaviorType::Flee;
    }
    else
    {
        behavior = BehaviorType::Idle;
    }
}

void Deer::update(float deltaTime)
{
    if (!flowField || !isAlive())
    {
        return;
    }

    int tileX = getTileX();
    int tileY = getTileY();
    float dirX = 0.0f, dirY = 0.0f;

    flowField->getDirectionAt(tileX, tileY, dirX, dirY);

    float length = std::sqrt(dirX * dirX + dirY * dirY);
    if (length > 0.0f)
    {
        dirX /= length;
        dirY /= length;

        // Si comportement = fuite, inverse la direction
        if (behavior == BehaviorType::Flee)
        {
            dirX = -dirX;
            dirY = -dirY;
        }

        x += dirX * speed * deltaTime;
        y += dirY * speed * deltaTime;
    }
}
