#include "player.hpp"
#include <cmath>
#include <logic/Map/map.hpp>

Player::Player(float startX, float startY, Map map)
    : map(std::move(map)), x(startX), y(startY), speed(2.5f), tileSize(1.0f), alive(true), score(0)
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

    int tileX = getTileX();
    int tileY = getTileY();
    if (tileX < 0 || tileY < 0) {
        return;
    }
    if (tileX >= 0 && tileY >= 0) {
        if (map.getMap()[tileX][tileY] == MapType::FLOWER) { 
            addScore(1);
            map.removeFlower(tileX, tileY);
        }
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

float Player::getSpeed() const
{
    return speed;
}

int Player::getScore() const
{
    return score;
}

void Player::addScore(int points)
{
    score += points;
}