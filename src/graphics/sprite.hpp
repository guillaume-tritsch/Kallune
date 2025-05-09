#pragma once

#include <glad/glad.h>
#include <string>

class Sprite {
public:
    Sprite(const std::string& imagePath, int width, int height);
    ~Sprite();

    void draw(float x, float y);

private:
    GLuint textureID;
    GLuint vao, vbo;
    int spriteWidth, spriteHeight;
    int textureWidth, textureHeight;

    void loadTexture(const std::string& path);
    void setupQuad();
};
