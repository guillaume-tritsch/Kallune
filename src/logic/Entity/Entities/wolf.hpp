#pragma once
#include "../../Player/player.hpp"
#include "../../Flowfield/flowfield.hpp"
#include "../entity.hpp"
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