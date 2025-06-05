#pragma once

class Player {
public:
    Player(float startX, float startY);

    void move(float dirX, float dirY, float deltaTime);
    void takeDamage(float amount);

    float getX() const;
    float getY() const;
    int getTileX() const;
    int getTileY() const;

    float getHealth() const;
    bool isAlive() const;

private:
    float x, y;               // position en unités
    float speed = 2.5f;       // vitesse en unités/seconde
    float health = 100.0f;
    float tileSize = 1.0f;    // taille d’une case (utile pour getTileX/Y)
};
