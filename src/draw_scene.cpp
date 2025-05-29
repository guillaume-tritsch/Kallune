#include "draw_scene.hpp"
#include <tuple>
#include <stb_image.h>
#include "graphics/sprite.hpp"

GLBI_Engine myEngine;

GLBI_Set_Of_Points originPoint;

Sprite* tile000 {};
Sprite* tile001 {};

void initScene()
{
	tile000 = new Sprite("tileset/tile_000.png", 0.2f, 0.2f);
	tile001 = new Sprite("tileset/tile_020.png", 0.2f, 0.2f);

	std::vector<float> origin = {0.0f, 0.0f};
	std::vector<float> originColor = {1.0f, 0.0f, 0.0f};
	originPoint.initSet(origin, originColor);
	originPoint.changeNature(GL_POINTS);
}

void drawScene()
{
	glClearColor(0.5f,0.5f,0.5f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

	originPoint.drawSet();

	myEngine.activateTexturing(true);

	glPointSize(10.0f);
	myEngine.setFlatColor(1.0f, 1.0f, 1.0f);
	glLineWidth(2.0f);
	
	// draw quad
	myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 0.0f));
		myEngine.updateMvMatrix();
		tile000->draw();
	myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addTranslation(Vector3D(0.2f, 0.2f, 0.2f));
		myEngine.updateMvMatrix();
		tile001->draw();
	myEngine.mvMatrixStack.popMatrix();
}
