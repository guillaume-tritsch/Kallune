#pragma once

#include "utils/entityType.hpp"

class Player;
class FlowField;

enum class BehaviorType {
    Idle,
    Attack,
    Flee
};

class Entity {
public:
    Entity(float startX, float startY);
    virtual ~Entity() = default;

    virtual void update(float deltaTime) = 0;
    virtual void decideBehavior(const Player& player) = 0;

    void setFlowField(const FlowField* field);

    float getX() const;
    float getY() const;
    int getTileX() const;
    int getTileY() const;

    bool isAlive() const;
    bool isAggressive() const;
    bool isCoward() const;

    void takeDamage(float dmg); 
    void setPlayer(const Player* p);
    void setPosition(float newX, float newY);

    EntityType getType() const;
protected:
    float x, y;
    float speed = 1.5f;
    float health = 100.0f;
    float tileSize = 1.0f;
    EntityType type;
    const FlowField* flowField = nullptr;
    BehaviorType behavior = BehaviorType::Idle;

    virtual bool aggressive() const = 0;
    virtual bool coward() const = 0;

    const Player* player = nullptr;

};
