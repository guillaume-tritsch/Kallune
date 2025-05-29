#include "draw_scene.hpp"
#include <tuple>
#include <stb_image.h>
#include "graphics/sprite.hpp"
#include <iomanip>
#include <sstream>

GLBI_Engine myEngine;

GLBI_Set_Of_Points originPoint;

std::vector<Sprite *> tileset;

void initScene()
{
	for (int i = 0; i < 114; ++i)
	{
		std::ostringstream ss;
		ss << "tileset/tile_" << std::setw(3) << std::setfill('0') << i << ".png";
		tileset.push_back(new Sprite(ss.str(), 0.2f, 0.2f));
	}

	std::vector<float> origin = {0.0f, 0.0f};
	std::vector<float> originColor = {1.0f, 0.0f, 0.0f};
	originPoint.initSet(origin, originColor);
	originPoint.changeNature(GL_POINTS);
}

void drawScene()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
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
	tileset[0]->draw();
	myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0.2f, 0.2f, 0.2f));
	myEngine.updateMvMatrix();
	tileset[113]->draw();
	myEngine.mvMatrixStack.popMatrix();
}
