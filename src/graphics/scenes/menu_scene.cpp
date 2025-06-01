#include "menu_scene.hpp"

MenuScene::MenuScene()
{
    background = new AnimatedSprite("menu/shorter-animation.png", 1.0f, 1.0f, 54, 1, 15);
    cursorSprite = new Sprite("cursors/crusor.png", 0.1f, 0.1f);

}

void MenuScene::draw()
{
    glClearColor(
        173.0f / 255.0f,
        119.0f / 255.0f,
        87.0f / 255.0f,
        1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    // glDepthFunc(GL_LEQUAL);

    myEngine.activateTexturing(true);

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 0.0f));
    myEngine.updateMvMatrix();
    background->update(1.0f / 60.0f);
    background->draw();
    myEngine.mvMatrixStack.popMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(mouseX / 100, mouseY / 100, 0.0f));
    myEngine.updateMvMatrix();

    cursorSprite->draw();

    myEngine.mvMatrixStack.popMatrix();
}