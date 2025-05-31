#pragma once
#include "../../Player/player.h"
#include "../../Flowfield/flowfield.h"
#include "../entity.h"
#include <cmath>

class Wolf : public Entity
{
public:
    Wolf(float startX, float startY);
    Wolf(float startX, float startY, const Player *player, const FlowField *flowField);

    void update(float deltaTime) override;
    void decideBehavior(const Player &player) override;

private:
    bool aggressive() const override { return true; }
    bool coward() const override { return false; }

    float attackRange = 1.5f;
    float attackCooldown = 1.0f;
    float timeSinceLastAttack = 0.0f;
};

Wolf::Wolf(float startX, float startY, const Player *player, const FlowField *flowField)
    : Entity(startX, startY)
{
    this->player = player;
    this->flowField = flowField;
    speed = 2.5f;
}

Wolf::Wolf(float startX, float startY) : Entity(startX, startY)
{
    speed = 2.5f; // Plus rapide que le sanglier
}

void Wolf::decideBehavior(const Player &player)
{
    float dx = player.getX() - x;
    float dy = player.getY() - y;
    float distanceSq = dx * dx + dy * dy;

    if (distanceSq < attackRange * attackRange)
    {
        behavior = BehaviorType::Attack;
    }
    else
    {
        behavior = BehaviorType::Idle;
    }
}

void Wolf::update(float deltaTime)
{
    if (!flowField || !isAlive())
    {
        return;
    }

    // Comportement
    switch (behavior)
    {
    case BehaviorType::Attack:
        timeSinceLastAttack += deltaTime;
        if (timeSinceLastAttack >= attackCooldown)
        {
            // Ici tu peux appeler une méthode pour infliger des dégâts au joueur
            // Exemple : player.takeDamage(10.0f);
            timeSinceLastAttack = 0.0f;
        }
        break;

    case BehaviorType::Idle:
    case BehaviorType::Flee:
    default:
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
        }
    }
    break;
    }
}
