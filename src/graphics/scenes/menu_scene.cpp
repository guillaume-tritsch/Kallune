#include "menu_scene.hpp"

MenuScene::MenuScene()
{
    // BACKGROUND
    animation = new AnimatedSprite("menu/background-spritesheet.png", 13.84f, 9.0f, 15, 16, 10);
    background = new Sprite("menu/menu-background.png", 4.9f, 9.0f);

    // BUTTONS
    playButton = new Sprite("menu/play-button.png", 3.31f, 0.99f);
    settingsButton = new Sprite("menu/settings-button.png", 1.55f, 0.99f);
    exitButton = new Sprite("menu/exit-button.png", 1.55f, 0.99f);
}

void MenuScene::draw(double deltaTime)
{
    glClearColor(
        173.0f / 255.0f,
        119.0f / 255.0f,
        87.0f / 255.0f,
        1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

    // BACKGROUND
    GameEngine.mvMatrixStack.pushMatrix();
        GameEngine.mvMatrixStack.addTranslation(Vector3D(8.0f - 13.84f / 2, 0.0f, 0.0f));
        GameEngine.updateMvMatrix();
        animation->update(deltaTime);
        animation->draw();
    GameEngine.mvMatrixStack.popMatrix();

    GameEngine.mvMatrixStack.pushMatrix();
        GameEngine.mvMatrixStack.addTranslation(Vector3D(-8.0f + 4.9f / 2, 0.0f, 0.0f));
        GameEngine.updateMvMatrix();
        background->draw();
    GameEngine.mvMatrixStack.popMatrix();

    // BUTTONS
    GameEngine.mvMatrixStack.pushMatrix();
        GameEngine.mvMatrixStack.addTranslation(Vector3D(-8.0f + 3.31f / 2 + 0.8f, -0.5f, 0.0f));
        GameEngine.updateMvMatrix();
        playButton->draw();
    GameEngine.mvMatrixStack.popMatrix();

    GameEngine.mvMatrixStack.pushMatrix();
        GameEngine.mvMatrixStack.addTranslation(Vector3D(-8.0f + 1.55f / 2 + 0.8f, -1.75f, 0.0f));
        GameEngine.updateMvMatrix();
        settingsButton->draw();
    GameEngine.mvMatrixStack.popMatrix();

    GameEngine.mvMatrixStack.pushMatrix();
        GameEngine.mvMatrixStack.addTranslation(Vector3D(-8.0f + 1.55f + 1.8f, -1.75f, 0.0f));
        GameEngine.updateMvMatrix();
        exitButton->draw();
    GameEngine.mvMatrixStack.popMatrix();
}