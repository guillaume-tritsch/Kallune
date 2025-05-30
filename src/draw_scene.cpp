#include "draw_scene.hpp"
#include <tuple>
#include <stb_image.h>
#include "graphics/sprite.hpp"
#include "graphics/animatedSprite.hpp"

GLBI_Engine myEngine;

AnimatedSprite* badger {};
AnimatedSprite* boar {};
AnimatedSprite* stag {};
AnimatedSprite* wolf {};

void initScene()
{
	badger = new AnimatedSprite("critters/badger/critter_badger_SE_walk.png", 0.7f, 0.7f, 9, 1, 30);
	boar = new AnimatedSprite("critters/boar/boar_SE_run_sheet.png", 0.6f, 0.4f, 2, 2, 20);
	stag = new AnimatedSprite("critters/stag/critter_stag_SE_walk.png", 0.7f, 0.7f, 11, 1, 30);
	wolf = new AnimatedSprite("critters/wolf/wolf-run.png", 1.0f, 1.0f, 8, 4, 30);
}

void drawScene()
{
	glClearColor(0.5f,0.5f,0.5f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

	myEngine.activateTexturing(true);
	
	// badger
	myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addTranslation(Vector3D(-1.5f, -1.5f, 0.0f));
		myEngine.updateMvMatrix();
		badger->update(1.0f / 60.0f);
		badger->draw();
	myEngine.mvMatrixStack.popMatrix();

	// boar
	myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addTranslation(Vector3D(1.5f, -1.5f, 0.0f));
		myEngine.updateMvMatrix();
		boar->update(1.0f / 60.0f);
		boar->draw();
	myEngine.mvMatrixStack.popMatrix();

	// stag
	myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addTranslation(Vector3D(-1.5f, 1.5f, 0.0f));
		myEngine.updateMvMatrix();
		stag->update(1.0f / 60.0f);
		stag->draw();
	myEngine.mvMatrixStack.popMatrix();

	// wolf
	myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addTranslation(Vector3D(1.5f, 1.5f, 0.0f));
		myEngine.updateMvMatrix();
		wolf->update(1.0f / 60.0f);
		wolf->draw();
	myEngine.mvMatrixStack.popMatrix();
}
