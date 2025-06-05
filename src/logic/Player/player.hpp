#pragma once

#include <logic/Map/map.hpp>

class Player {
public:
    Player(float startX, float startY, Map map);

    void move(float dirX, float dirY, float deltaTime);
    void takeDamage(float amount);


    void setPosition(float newX, float newY);
    float getX() const;
    float getY() const;
    int getTileX() const;
    int getTileY() const;

    bool isAlive() const;
    void kill();

    float getSpeed() const;

    int getScore() const;
    void addScore(int points);

    void resetScore() { score = 0; }



private:
    float x, y;               // position en unités
    float speed = 2.5f;       // vitesse en unités/seconde
    bool alive = true;
    float tileSize = 1.0f;    // taille d’une case (utile pour getTileX/Y)

    int score = 0;
    Map map;
};
