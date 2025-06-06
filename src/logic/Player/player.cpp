#include "player.hpp"
#include <cmath>
#include <logic/Map/map.hpp>
#include "utils/directions.hpp"
#include "utils/behavior.hpp"

Player::Player(float startX, float startY, Map map)
    : map(std::move(map)), x(startX), y(startY), speed(5.f), tileSize(1.0f), alive(true), score(0)
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
    if (tileX >= 0 && tileY >= 0 && tileX < map.getWidth() && tileY < map.getHeight()) {
        if (map.getMap()[tileX][tileY] == MapType::FLOWER) { 
            addScore(1);
            cout << "Player collected a flower at (" << tileX << ", " << tileY << "). Score: " << score << std::endl;
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

void Player::calculateDirectionAndBehavior(float dirX, float dirY)
{
        if (dirX > 0.0f)
            direction = Direction::EAST;
        else if (dirX < 0.0f)
            direction = Direction::WEST;
        else if (dirY > 0.0f)
            direction = Direction::SOUTH;
        else if (dirY < 0.0f)
            direction = Direction::NORTH;

        if (dirX == 0.0f && dirY == 0.0f) {
            behavior = BehaviorType::IDLE;
        } else {
            behavior = BehaviorType::ATTACK;
        }
}