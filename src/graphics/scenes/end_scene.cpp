#include "end_scene.hpp"

EndScene::EndScene()
{
    float sizeZ = 0.3f;
    logoSprite = new Sprite("game_over/logo_blaireau.png", 0.5f, 0.5f);

    float sizeX = sizeZ * (1335.0f / 335.0f); // 0.5 * 4 = 2.0f
    texteSprite = new Sprite("game_over/texte_fin.png", sizeX, sizeZ);

    sizeX = sizeZ * (1071.0f / 276.0f);
    buttonSprite = new Sprite("game_over/bouton_retour_menu.png", sizeX, sizeZ);

    cursorSprite = new Sprite("cursors/crusor.png", 0.1f, 0.1f);
    cursorAnimatedSprite = new AnimatedSprite("cursors/animated_cursor.png", 0.1f, 0.1f, 3, 1, 15);
}

void EndScene::draw()
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
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 1.0f, 0.0f));
    myEngine.updateMvMatrix();
    logoSprite->draw();
    myEngine.mvMatrixStack.popMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, -0.5f, 0.0f));
    myEngine.updateMvMatrix();
    texteSprite->draw();
    myEngine.mvMatrixStack.popMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, -2.0f, 0.0f));
    myEngine.updateMvMatrix();
    buttonSprite->draw();
    myEngine.mvMatrixStack.popMatrix();

    // Draw the cursor at the end
    if (cursorClicked)
    {
        cursorAnimatedSprite->update(1.0f / 60.0f);
        myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation(Vector3D(x_world, y_world, 0.0f));
        myEngine.updateMvMatrix();
        cursorAnimatedSprite->draw();
        myEngine.mvMatrixStack.popMatrix();
    }
    else
    {
        myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation(Vector3D(x_world, y_world, 0.0f));
        myEngine.updateMvMatrix();
        cursorSprite->draw();
        myEngine.mvMatrixStack.popMatrix();
    }
}