#include "player.hpp"
#include <cmath>

Player::Player(float startX, float startY)
    : x(startX), y(startY), health(100.0f), speed(2.5f), tileSize(1.0f)
{
}

void Player::move(float dirX, float dirY, float deltaTime)
{
    // Normaliser la direction pour éviter un déplacement plus rapide en diagonale
    float length = std::sqrt(dirX * dirX + dirY * dirY);
    if (length > 0.0f) {
        dirX /= length;
        dirY /= length;
        
        x += dirX * speed * deltaTime;
        y += dirY * speed * deltaTime;
    }
}

void Player::takeDamage(float amount)
{
    health -= amount;
    if (health < 0.0f) {
        health = 0.0f;
    }
}

float Player::getX() const
{
    return x;
}

float Player::getY() const
{
    return y;
}

int Player::getTileX() const
{
    return static_cast<int>(x / tileSize);
}

int Player::getTileY() const
{
    return static_cast<int>(y / tileSize);
}

float Player::getHealth() const
{
    return health;
}

bool Player::isAlive() const
{
    return health > 0.0f;
}
