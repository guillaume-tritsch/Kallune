#include "player.hpp"
#include <cmath>

Player::Player(float startX, float startY)
    : x(startX), y(startY), speed(2.5f), tileSize(1.0f), alive(true)
{
}

void Player::move(float dirX, float dirY, float deltaTime)
{
    float length = std::sqrt(dirX * dirX + dirY * dirY);
    if (length > 0.0f) {
        dirX /= length;
        dirY /= length;
        
        x += dirX * speed * deltaTime;
        y += dirY * speed * deltaTime;
    }
}

void Player::kill()
{
    alive = false;
}

void Player::setPosition(float newX, float newY)
{
    x = newX;
    y = newY;
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

bool Player::isAlive() const
{
    return alive;
}
