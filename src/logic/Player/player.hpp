#pragma once

class Player {
public:
    Player(float startX, float startY);

    void move(float dirX, float dirY, float deltaTime);
    void takeDamage(float amount);


    void setPosition(float newX, float newY);
    float getX() const;
    float getY() const;
    int getTileX() const;
    int getTileY() const;

    bool isAlive() const;
    void kill();
private:
    float x, y;               // position en unités
    float speed = 2.5f;       // vitesse en unités/seconde
    bool alive = true;
    float tileSize = 1.0f;    // taille d’une case (utile pour getTileX/Y)
};
