#include "draw_scene.hpp"
#include <tuple>
#include <stb_image.h>

GLBI_Engine myEngine;
StandardMesh* rectangle;

GLBI_Texture myTexture {};

void initScene()
{
	const char *filename{"assets/images/tileset/tile_000.png"};
	int x, y, n;
	unsigned char *imageData{stbi_load(filename, &x, &y, &n, 0)};
	myTexture.createTexture();
	myTexture.setParameters(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	myTexture.setParameters(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	myTexture.setParameters(GL_PIXEL_MODE_BIT, GL_RGBA);
	myTexture.loadImage(x, y, n, imageData);
	rectangle = basicRect(10.0,10.0);
	rectangle->createVAO();

	stbi_image_free((void *)imageData);
}

void drawScene()
{
	glClearColor(0.f,0.0f,0.2f,0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		// glDisable(GL_BLEND);

	myEngine.setFlatColor(0.5, 1.0, 0.0);
	myEngine.activateTexturing(true);

	// draw quad
	myEngine.mvMatrixStack.pushMatrix();
	// myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 0.0f));
	myEngine.updateMvMatrix();
	// myTexture.attachTexture();
	rectangle->draw();
	// myTexture.detachTexture();
	myEngine.mvMatrixStack.popMatrix();
}
