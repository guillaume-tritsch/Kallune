#include "deer.hpp"
#include "utils/entityType.hpp"

Deer::Deer(float startX, float startY) : Entity(startX, startY)
{
    speed = 2.0f;
    type = EntityType::DEER;
}

Deer::Deer(float startX, float startY, const Player *player, const FlowField *flowField)
    : Entity(startX, startY)
{
    this->player = player;
    this->flowField = flowField;
    speed = 2.0f;
}

void Deer::decideBehavior(Player &player)
{
    float dx = player.getX() - x;
    float dy = player.getY() - y;
    float distanceSq = std::sqrt(dx * dx + dy * dy);

    if (distanceSq < fleeDistance)
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

    switch (behavior)
    {
    case BehaviorType::Attack:
    case BehaviorType::Idle:
            x += ((rand() % 100 < 50) ? 1 : -1) * speed * deltaTime;
            y += ((rand() % 100 < 50) ? 1 : -1) * speed * deltaTime;
    case BehaviorType::Flee:
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
        }

        break;
    }
}
