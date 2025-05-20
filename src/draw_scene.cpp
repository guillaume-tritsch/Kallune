#include "draw_scene.hpp"
#include <tuple>
#include <stb_image.h>

/// Camera parameters
float angle_theta{45.0}; // Angle between x axis and viewpoint
float angle_phy{30.0};	 // Angle between z axis and viewpoint
float dist_zoom{30.0};	 // Distance between origin and viewpoint

GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
GLBI_Convex_2D_Shape ground{3};
GLBI_Convex_2D_Shape circle{3};
StandardMesh* rectangle;

GLBI_Set_Of_Points frame(3);

GLBI_Texture myTexture {};

IndexedMesh *sphere;
StandardMesh *cone;

float degToRad(float const &angle)
{
	return (angle * M_PI / 2) / 90;
}

std::tuple<float, float, float> colorConvertor(int const &r, int const &g, int const &b)
{
	return {static_cast<float>(r) / 255.0f,
			static_cast<float>(g) / 255.0f,
			static_cast<float>(b) / 255.0f};
}

std::tuple<float, float, float> colorConvertor(int const &color)
{
	return {static_cast<float>(color) / 255.0f,
			static_cast<float>(color) / 255.0f,
			static_cast<float>(color) / 255.0f};
}

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
	// sphere = basicSphere();
	// sphere->createVAO();

	// cone = basicCone(10, 2);
	// cone->createVAO();

	// std::vector<float> points{0.0, 0.0, 0.0};
	// somePoints.initSet(points, 1.0, 1.0, 1.0);

	// std::vector<float> baseCarre{-10.0, -10.0, 0.0,
	// 							 10.0, -10.0, 0.0,
	// 							 10.0, 10.0, 0.0,
	// 							 -10.0, 10.0, 0.0};
	// ground.initShape(baseCarre);
	// ground.changeNature(GL_TRIANGLE_FAN);

	// std::vector<float> coord_point{0.0f, 0.0f, 0.0f};

	// std::vector<float> coord_circle{0.0f, 0.0f, 0.0f};

	// for (int i{1}; i < 100; i++)
	// {
	// 	coord_circle.push_back(sin(static_cast<float>(i) / M_PI));
	// 	coord_circle.push_back(cos(static_cast<float>(i) / M_PI));
	// 	coord_circle.push_back(0.0f);
	// }

	// circle.initShape(coord_circle);
	// circle.changeNature(GL_TRIANGLE_FAN);

	stbi_image_free((void *)imageData);

	drawFrame();
}

void drawFrame()
{
	std::vector<float> axes{0.0, 0.0, 0.0,
							10.0, 0.0, 0.0,
							0.0, 0.0, 0.0,
							0.0, 10.0, 0.0,
							0.0, 0.0, 0.0,
							0.0, 0.0, 10.0};

	std ::vector<float> colors{1.0, 0.0, 0.0,
							   1.0, 0.0, 0.0,
							   0.0, 1.0, 0.0,
							   0.0, 1.0, 0.0,
							   0.0, 0.0, 1.0,
							   0.0, 0.0, 1.0};

	frame.initSet(axes, colors);
	frame.changeNature(GL_LINES);
}

int i = 0;

void drawScene()
{
	// glPointSize(10.0);

	frame.drawSet();

	glClearColor(0.f,0.0f,0.2f,0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		// glDisable(GL_BLEND);

	myEngine.setFlatColor(0.2, 1.0, 0.0);
	myEngine.activateTexturing(true);

	// draw quad
	myEngine.mvMatrixStack.pushMatrix();
	// myTexture.attachTexture();
	rectangle->draw();
	// myTexture.detachTexture();
	myEngine.mvMatrixStack.popMatrix();


	// ground.drawShape();

	// myEngine.mvMatrixStack.pushMatrix();
	// myEngine.mvMatrixStack.addTranslation(Vector3D(4.0f, 0.0f, 5.0f));
	// myEngine.updateMvMatrix();
	// myEngine.mvMatrixStack.addHomothety(3.0f);
	// myEngine.updateMvMatrix();
	// myEngine.setFlatColor(1.0f, 1.0f, 1.0f);
	// sphere->draw();
	// myEngine.mvMatrixStack.popMatrix();

	// myEngine.mvMatrixStack.pushMatrix();
	// myEngine.mvMatrixStack.addTranslation(Vector3D(cos(i * 0.1) * 5.0f, sin(i * 0.1) * 5.0f, 0.0f));
	// myEngine.updateMvMatrix();
	// myEngine.setFlatColor(1.0f, 1.0f, 1.0f);
	// sphere->draw();
	// myEngine.mvMatrixStack.popMatrix();
	// i++;

	// drawBase();
	// myEngine.mvMatrixStack.pushMatrix();
	// myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 10.0f));
	// myEngine.updateMvMatrix();
	// drawArm();
	// myEngine.mvMatrixStack.popMatrix();

	// drawPan();
}
