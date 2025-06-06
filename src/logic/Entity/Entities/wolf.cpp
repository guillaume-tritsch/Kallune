#include "wolf.hpp"
#include "utils/entityType.hpp"

Wolf::Wolf(float startX, float startY, const Player *player, const FlowField *flowField)
    : Entity(startX, startY)
{
    this->player = player;
    this->flowField = flowField;
    speed = 2.5f;
    type = EntityType::WOLF;
}

Wolf::Wolf(float startX, float startY) : Entity(startX, startY)
{
    speed = 2.5f; // Plus rapide que le sanglier
}

void Wolf::decideBehavior(Player &player)
{
    float dx = player.getX() - x;
    float dy = player.getY() - y;
    float distanceSq = std::sqrt(dx * dx + dy * dy);

    if (distanceSq < 0.5f)
    {
        player.kill();
    }
    else if (distanceSq < pursuitRange)
    {
        behavior = BehaviorType::ATTACK;
    }
    else
    {
        behavior = BehaviorType::IDLE;
    }
    return;
}

void Wolf::update(float deltaTime)
{
    if (!flowField || !isAlive())
    {
        return;
    }

    switch (behavior)
    {
    case BehaviorType::ATTACK:
    {
        int tileX = getTileX();
        int tileY = getTileY();
        float dirX = 0.0f, dirY = 0.0f;

        flowField->getDirectionAt(tileX, tileY, dirX, dirY);

        float length = std::sqrt(dirX * dirX + dirY * dirY);
        if (length > 0.0f)
        {
            dirX /= length;
            dirY /= length;

            x += dirX * speed * deltaTime;
            y += dirY * speed * deltaTime;

            calculateDirection(x, y);
        }
        break;
    }
    case BehaviorType::IDLE:
    {
        x += ((rand() % 100 < 50) ? 1 : -1) * speed * deltaTime;
        y += ((rand() % 100 < 50) ? 1 : -1) * speed * deltaTime;
        calculateDirection(x, y);
        break;
    }
    case BehaviorType::FLEE:
    {
        break;
    }
    }
}
