#pragma once
#include "../../Player/player.hpp"
#include "../../Flowfield/flowfield.hpp"
#include "../entity.hpp"
#include <cmath>

class Boar : public Entity
{
public:
    Boar(float startX, float startY);
    Boar(float startX, float startY, const Player* player, const FlowField* flowField);

    void update(float deltaTime) override;
    void decideBehavior(const Player& player) override;

private:
    bool aggressive() const override { return true; }
    bool coward() const override { return false; }

    float attackRange = 1.2f;
    float attackCooldown = 2.0f;
    float timeSinceLastAttack = 0.0f;
};