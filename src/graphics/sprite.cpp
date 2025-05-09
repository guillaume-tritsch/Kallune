#include "sprite.hpp"
#include <stb_image.h>
#include <iostream>

Sprite::Sprite(const std::string& imagePath, int width, int height)
    : spriteWidth(width), spriteHeight(height) {
    loadTexture(imagePath);
    std::cout << "Loaded texture: " << imagePath << std::endl;
    setupQuad();
}

Sprite::~Sprite() {
    glDeleteTextures(1, &textureID);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Sprite::loadTexture(const std::string& path) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int channels;
    unsigned char* data = stbi_load(path.c_str(), &textureWidth, &textureHeight, &channels, 4);
    if (!data) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Sprite::setupQuad() {
    float vertices[] = {
        // positions   // texCoords
        0.0f, 0.0f,     0.0f, 1.0f,
        1.0f, 0.0f,     1.0f, 1.0f,
        1.0f, 1.0f,     1.0f, 0.0f,
        0.0f, 1.0f,     0.0f, 0.0f
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // pos
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texCoord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Sprite::draw(float x, float y) {
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBindVertexArray(vao);

    glUniform2f(glGetUniformLocation(0, "spriteOffset"), 0.0f, 0.0f);
    glUniform2f(glGetUniformLocation(0, "spriteScale"),
                static_cast<float>(spriteWidth) / textureWidth,
                static_cast<float>(spriteHeight) / textureHeight);
    glUniform2f(glGetUniformLocation(0, "position"), x, y);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
