#include "glew.h"
#include "freeglut.h"
#include "glm.hpp"
#include "ext.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <cstdio>

#include "Shader_Loader.h"
#include "Render_Utils.h"
#include "Camera.h"
#include "Texture.h"
#include "Asteroid.h"
#include "Planet.h"
#include "Sun.h"
#include "Ship.h"
#include "Skybox.h"
#include <memory>

GLuint programSkybox;
GLuint programColor;
GLuint programTexture;
GLuint programSun;
GLuint programSight;
GLuint programBump;

Core::Shader_Loader shaderLoader;

obj::Model shipModel;
obj::Model sphereModel;
obj::Model saturnModel;
obj::Model planeModel;
obj::Model ufoModel;

glm::vec3 cameraPos = glm::vec3(300, 2, 300);
glm::vec3 cameraDir; // Wektor "do przodu" kamery
glm::vec3 cameraSide; // Wektor "w bok" kamery
float cameraAngle = 0;

glm::mat4 cameraMatrix, perspectiveMatrix;

glm::vec3 lightDir = glm::normalize(glm::vec3(1.0f, -0.9f, -1.0f));

glm::vec3 sunPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 sunPos2 = glm::vec3(1000.0f, -800.0f, -500.0f);
glm::vec3 sunColor = glm::vec3(1.0f, 0.5f, 0.2f);

glm::mat4 planetDefaultMatrix = glm::translate(glm::vec3(0.0f));
glm::mat4 sightDefaultMatrix = glm::translate(glm::vec3(100000.0f));

glm::quat rotation = glm::quat(1, 0, 0, 0);
float shipAngle = glm::radians(180.0f);

GLuint textureAsteroid;
GLuint textureAsteroid_normals;
GLuint textureJupiter;
GLuint textureMars;
GLuint textureVenus;
GLuint textureMercury;
GLuint textureEarth;
GLuint textureSaturn;
GLuint textureUranus;
GLuint textureNeptune;
GLuint textureSun;

glm::vec3 mercuryTranslate = glm::vec3(0.0f);
glm::vec3 mercury2Translate = glm::vec3(0.0f);
glm::vec3 venusTranslate = glm::vec3(0.0f);
glm::vec3 venus2Translate = glm::vec3(0.0f);
glm::vec3 earthTranslate = glm::vec3(0.0f);
glm::vec3 earth2Translate = glm::vec3(0.0f);
glm::vec3 marsTranslate = glm::vec3(0.0f);
glm::vec3 mars2Translate = glm::vec3(0.0f);
glm::vec3 jupiterTranslate = glm::vec3(0.0f);
glm::vec3 jupiter2Translate = glm::vec3(0.0f);
glm::vec3 saturnTranslate = glm::vec3(0.0f);
glm::vec3 saturn2Translate = glm::vec3(0.0f);
glm::vec3 uranusTranslate = glm::vec3(0.0f);
glm::vec3 uranus2Translate = glm::vec3(0.0f);
glm::vec3 neptuneTranslate = glm::vec3(0.0f);
glm::vec3 neptune2Translate = glm::vec3(0.0f);


GLuint textureId;

glm::vec3 wspolrzedne[400];
glm::vec3 wspolrzedneUfo[4] = {
	glm::vec3(0.0f), glm::vec3(40.0f), glm::vec3(80.0f), glm::vec3(120.0f)
};
glm::vec3 wektor[4] = {
	glm::vec3(0.0f), glm::vec3(40.0f), glm::vec3(80.0f), glm::vec3(120.0f)
};

int roznicaX;
int roznicaY;
int ostatniX = 300;
int ostatniY = 300;
int roznicaZ;
int counter = 0;
float lastTimeF = -1.0f;
glm::quat lastRotation;
glm::mat4 lastCameraMatrix;

bool mouseKeyDown = false;
bool freeLook = false;

float appLoadingTime;

void keyboard(unsigned char key, int x, int y)
{
	
	float angleSpeed = 0.1f;
	//float moveSpeed = 0.1f;
	float moveSpeed = 10.0f;
	switch(key)
	{
	case 'z': roznicaZ = -20.0f; break;
	case 'x': roznicaZ = 20.0f; break;
	case 'w': cameraPos += cameraDir * moveSpeed; break;
	case 's': cameraPos -= cameraDir * moveSpeed; break;
	case 'd': cameraPos += cameraSide * moveSpeed; break;
	case 'a': cameraPos -= cameraSide * moveSpeed; break;
	case 'm': shipAngle += glm::radians(2.0f); break;
	case 'f': freeLook = !freeLook; lastRotation = rotation; break;
	}
}

void mouse(int x, int y)
{
	roznicaX = x - ostatniX;
	roznicaY = y - ostatniY;
	ostatniX = x;
	ostatniY = y;
}

void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		if (mouseKeyDown) {
			mouseKeyDown = false;
			cameraPos -= cameraDir * 50.0f;
		}
		else {
			mouseKeyDown = true;
			cameraPos += cameraDir * 50.0f;
		}
	}
}

glm::vec3 predictMove() {
	float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f - appLoadingTime;
	int sekundaRuchu = int(floorf(time));
	float u³amekSekundy = time - sekundaRuchu;
	wektor[0] = wspolrzedneUfo[(sekundaRuchu - 1) % 4];
	wektor[1] = wspolrzedneUfo[(sekundaRuchu) % 4];
	wektor[2] = wspolrzedneUfo[(sekundaRuchu + 1) % 4];
	wektor[3] = wspolrzedneUfo[(sekundaRuchu + 2) % 4];
	glm::vec3 catmull = glm::catmullRom(wektor[0], wektor[1], wektor[2], wektor[3], u³amekSekundy);
	wspolrzedneUfo[0] = wspolrzedneUfo[1];
	wspolrzedneUfo[1] = wspolrzedneUfo[2];
	wspolrzedneUfo[2] = wspolrzedneUfo[3];
	glm::vec3 newUfo3 = wspolrzedneUfo[3] + glm::sphericalRand(0.5f);
	bool isCloser = glm::length(newUfo3 - (cameraPos + cameraDir * 0.5f)) < glm::length(wspolrzedneUfo[3] - (cameraPos + cameraDir * 0.5f));
	bool isSun = glm::length(newUfo3 - sunPos) < 140.0f || glm::length(newUfo3 - sunPos2) < 140.0f;
	bool isPlanet = glm::length(newUfo3 - mercuryTranslate) < 19.2f || glm::length(newUfo3 - mercury2Translate) < 19.2f || glm::length(newUfo3 - venusTranslate) < 36.3f
		&& glm::length(newUfo3 - venus2Translate) < 36.3f || glm::length(newUfo3 - earthTranslate) < 38.1f || glm::length(newUfo3 - earth2Translate) < 38.1f
		&& glm::length(newUfo3 - marsTranslate) < 27.2f || glm::length(newUfo3 - mars2Translate) < 38.1f || glm::length(newUfo3 - jupiterTranslate) < 100.0f
		&& glm::length(newUfo3 - jupiter2Translate) < 100.0f || glm::length(newUfo3 - saturnTranslate) < 150.0f || glm::length(newUfo3 - saturn2Translate) < 150.0f
		&& glm::length(newUfo3 - uranusTranslate) < 80.0f || glm::length(newUfo3 - uranus2Translate) < 80.0f || glm::length(newUfo3 - neptuneTranslate) < 78.0f
		&& glm::length(newUfo3 - neptune2Translate) < 78.0f;
	bool isAsteroid = false;
	for (auto i : wspolrzedne) {
		if (glm::length(newUfo3 - i) < 2.0f) {
			isAsteroid = true;
			break;
		}
	}
	while (isCloser || (isSun || isPlanet || isAsteroid)) {
		newUfo3 = wspolrzedneUfo[3] + glm::sphericalRand(0.5f);
		isCloser = glm::length(newUfo3 - (cameraPos + cameraDir * 0.5f)) < glm::length(wspolrzedneUfo[3] - (cameraPos + cameraDir * 0.5f));
		isSun = isSun = glm::length(newUfo3 - sunPos) < 140.0f || glm::length(newUfo3 - sunPos2) < 140.0f;
		isPlanet = glm::length(newUfo3 - mercuryTranslate) < 19.2f || glm::length(newUfo3 - mercury2Translate) < 19.2f || glm::length(newUfo3 - venusTranslate) < 36.3f
			&& glm::length(newUfo3 - venus2Translate) < 36.3f || glm::length(newUfo3 - earthTranslate) < 38.1f || glm::length(newUfo3 - earth2Translate) < 38.1f
			&& glm::length(newUfo3 - marsTranslate) < 27.2f || glm::length(newUfo3 - mars2Translate) < 38.1f || glm::length(newUfo3 - jupiterTranslate) < 100.0f
			&& glm::length(newUfo3 - jupiter2Translate) < 100.0f || glm::length(newUfo3 - saturnTranslate) < 150.0f || glm::length(newUfo3 - saturn2Translate) < 150.0f
			&& glm::length(newUfo3 - uranusTranslate) < 80.0f || glm::length(newUfo3 - uranus2Translate) < 80.0f || glm::length(newUfo3 - neptuneTranslate) < 78.0f
			&& glm::length(newUfo3 - neptune2Translate) < 78.0f;
		isAsteroid = false;
		for (auto i : wspolrzedne) {
			if (glm::length(newUfo3 - i) < 2.0f) {
				isAsteroid = true;
				break;
			}
		}
	}
	wspolrzedneUfo[3] = newUfo3;
	return catmull;
}


glm::mat4 createCameraMatrix()
{
	glm::quat Xangle = glm::angleAxis(glm::radians(roznicaX * 1.f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat Yangle = glm::angleAxis(glm::radians(roznicaY * 1.f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat Zangle = glm::angleAxis(glm::radians(roznicaZ * 1.f), glm::vec3(0.0f, 0.0f, 1.0f));
	roznicaX = 0;
	roznicaY = 0;
	roznicaZ = 0;
	glm::quat rotationChange = Xangle * Yangle * Zangle;
	rotation = rotationChange * rotation;
	rotation = glm::normalize(rotation);
	cameraDir = glm::inverse(rotation) * glm::vec3(0.0f, 0.0f, -1.0f);
	cameraSide = glm::inverse(rotation) * glm::vec3(1.0f, 0.0f, 0.0f);

	return Core::createViewMatrixQuat(cameraPos, rotation);
}

void createObjects() {
	for (int i = 0; i < 70; i++) {
		glm::vec2 asteroid2D = glm::circularRand(500.0f);
		wspolrzedne[i] = glm::vec3(asteroid2D.x, rand() % 50 - 50, asteroid2D.y);
	}
	for (int i = 70; i < 140; i++) {
		glm::vec2 asteroid2D = glm::circularRand(550.0f);
		wspolrzedne[i] = glm::vec3(asteroid2D.x, rand() % 50 - 50, asteroid2D.y);
	}
	for (int i = 140; i < 210; i++) {
		glm::vec2 asteroid2D = glm::circularRand(500.0f);
		wspolrzedne[i] = glm::vec3(asteroid2D.x + sunPos2.x, rand() % 50 - 50 + sunPos2.y, asteroid2D.y + sunPos2.z);
	}
	for (int i = 210; i < 280; i++) {
		glm::vec2 asteroid2D = glm::circularRand(550.0f);
		wspolrzedne[i] = glm::vec3(asteroid2D.x + sunPos2.x, rand() % 50 - 50 + sunPos2.y, asteroid2D.y + sunPos2.z);
	}

	std::shared_ptr<Ship>  ship = Ship::create(programColor, &shipModel, sunPos, sunPos2, glm::vec3(0.6f));
	std::shared_ptr<Ship> ufo = Ship::create(programColor, &ufoModel, sunPos, sunPos2, glm::vec3(0.6f));

	std::shared_ptr<Sun> sun1 = Sun::create(programSun, &sphereModel, glm::translate(sunPos) * glm::scale(glm::vec3(8 * 14.0f)),sunPos,sunPos2,textureSun);
	std::shared_ptr<Sun> sun2 = Sun::create(programSun, &sphereModel, glm::translate(sunPos2) * glm::scale(glm::vec3(8 * 14.0f)), sunPos, sunPos2, textureSun);


	for (int i = 0; i < 280; i++) {
		std::shared_ptr<Asteroid> asteroid = Asteroid::create(programBump, &sphereModel, glm::translate(wspolrzedne[i]), textureAsteroid, sunPos, sunPos2);
		asteroid->setNormal(textureAsteroid_normals);
	}

	std::shared_ptr<Planet> mercury = Planet::create(programTexture, &sphereModel, planetDefaultMatrix, textureMercury, sunPos, sunPos2);
	std::shared_ptr<Planet> venus = Planet::create(programTexture, &sphereModel, planetDefaultMatrix, textureVenus, sunPos, sunPos2);
	std::shared_ptr<Planet> earth = Planet::create(programTexture, &sphereModel, planetDefaultMatrix, textureEarth, sunPos, sunPos2);
	std::shared_ptr<Planet> mars = Planet::create(programTexture, &sphereModel, planetDefaultMatrix, textureMars, sunPos, sunPos2);
	std::shared_ptr<Planet> jupiter = Planet::create(programTexture, &sphereModel, planetDefaultMatrix, textureJupiter, sunPos, sunPos2);
	std::shared_ptr<Planet> saturn = Planet::create(programTexture, &saturnModel, planetDefaultMatrix, textureSaturn, sunPos, sunPos2);
	std::shared_ptr<Planet> uranus = Planet::create(programTexture, &sphereModel, planetDefaultMatrix, textureUranus, sunPos, sunPos2);
	std::shared_ptr<Planet> neptune = Planet::create(programTexture, &sphereModel, planetDefaultMatrix, textureNeptune, sunPos, sunPos2);

	std::shared_ptr<Planet> mercury2 = Planet::create(programTexture, &sphereModel, planetDefaultMatrix, textureMercury, sunPos, sunPos2);
	std::shared_ptr<Planet> venus2 = Planet::create(programTexture, &sphereModel, planetDefaultMatrix, textureVenus, sunPos, sunPos2);
	std::shared_ptr<Planet> earth2 = Planet::create(programTexture, &sphereModel, planetDefaultMatrix, textureEarth, sunPos, sunPos2);
	std::shared_ptr<Planet> mars2 = Planet::create(programTexture, &sphereModel, planetDefaultMatrix, textureMars, sunPos, sunPos2);
	std::shared_ptr<Planet> jupiter2 = Planet::create(programTexture, &sphereModel, planetDefaultMatrix, textureJupiter, sunPos, sunPos2);
	std::shared_ptr<Planet> saturn2 = Planet::create(programTexture, &saturnModel, planetDefaultMatrix, textureSaturn, sunPos, sunPos2);
	std::shared_ptr<Planet> uranus2 = Planet::create(programTexture, &sphereModel, planetDefaultMatrix, textureUranus, sunPos, sunPos2);
	std::shared_ptr<Planet> neptune2 = Planet::create(programTexture, &sphereModel, planetDefaultMatrix, textureNeptune, sunPos, sunPos2);

	std::shared_ptr<Planet> gunSight1 = Planet::create(programSight, &planeModel, sightDefaultMatrix, sunPos, sunPos2);
	std::shared_ptr<Planet> gunSight2 = Planet::create(programSight, &planeModel, sightDefaultMatrix, sunPos, sunPos2);
}

void drawObjects() {
	float timeF = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	cameraMatrix = createCameraMatrix();
	perspectiveMatrix = Core::createPerspectiveMatrix();

	glm::mat4 shipModelMatrix;
	glm::mat4 shipInitialTransformation;
	if (!mouseKeyDown) {
		shipInitialTransformation = glm::translate(glm::vec3(0, -0.25f, 0)) * glm::rotate(shipAngle, glm::vec3(0, 1, 0)) * glm::scale(glm::vec3(0.0008f));
	}
	else {
		shipInitialTransformation = glm::translate(glm::vec3(0, -0.15f, 0.3f)) * glm::rotate(shipAngle, glm::vec3(0, 1, 0)) * glm::scale(glm::vec3(0.0008f));
	}
	if (freeLook) {
		shipModelMatrix = glm::translate(cameraPos + cameraDir * 0.5f) * glm::mat4_cast(glm::inverse(lastRotation)) * shipInitialTransformation;
	}
	else {
		
		shipModelMatrix = glm::translate(cameraPos + cameraDir * 0.5f) * glm::mat4_cast(glm::inverse(rotation)) * shipInitialTransformation;
	}
	glm::mat4 planetRotation = glm::rotate(3.14f / 2.f * timeF / 2, glm::vec3(0.0f, 1.0f, 0.0f));

	int ctr = 0;
	for (auto obj : Ship::ship_objects) {
		if (ctr == 0) {
			obj->setMatrix(shipModelMatrix);
		}
		if (ctr == 1) {
			obj->setMatrix(glm::translate(predictMove()) * glm::scale(glm::vec3(4.0f)));
			
		}
		obj->draw(obj->getColor(), cameraPos, perspectiveMatrix, cameraMatrix);
		ctr++;
	}
	for (auto obj : Sun::sun_objects) {
		obj->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	}
	for (auto obj : Asteroid::asteroid_objects) {
		obj->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	}
	for (auto obj : Planet::planet_objects) {
		if (counter == 0) {
			mercuryTranslate = glm::vec3(sunPos.x + 170.0f * sinf(timeF / 8), sunPos.y, sunPos.z + 170.0f * cosf(timeF / 8));
			obj->setMatrix(glm::translate(mercuryTranslate) * planetRotation * glm::scale(glm::vec3(20 * 0.48f)));
		}
		if (counter == 1) {
			venusTranslate = glm::vec3(sunPos.x + -260.0f * sinf(timeF / 10), sunPos.y, sunPos.z + -260.0f * cosf(timeF / 10));
			obj->setMatrix(glm::translate(venusTranslate) * planetRotation * glm::scale(glm::vec3(15 * 1.21f)));
		}
		if (counter == 2) {
			earthTranslate = glm::vec3(sunPos.x + 350.0f * sinf(timeF / 12), sunPos.y, sunPos.z + 350.0f * cosf(timeF / 12));
			obj->setMatrix(glm::translate(earthTranslate) * planetRotation * glm::scale(glm::vec3(15 * 1.27f)));
		}
		if (counter == 3) {
			marsTranslate = glm::vec3(sunPos.x + -440.0f * sinf(timeF / 14), sunPos.y, sunPos.z + -440.0 * cosf(timeF / 14));
			obj->setMatrix(glm::translate(marsTranslate) * planetRotation * glm::scale(glm::vec3(20 * 0.68f)));
		}
		if (counter == 4) {
			jupiterTranslate = glm::vec3(sunPos.x + 800.0f * sinf(timeF / 16), sunPos.y, sunPos.z + 800.0f * cosf(timeF / 16));
			obj->setMatrix(glm::translate(jupiterTranslate) * planetRotation * glm::scale(glm::vec3(7 * 7.1f)));
		}
		if (counter == 5) {
			saturnTranslate = glm::vec3(sunPos.x + -1100.0f * sinf(timeF / 18), sunPos.y, sunPos.z + -1100.0f * cosf(timeF / 18));
			obj->setMatrix(glm::translate(saturnTranslate) * planetRotation * glm::rotate(glm::radians(90.0f), glm::vec3(1, 0, 0)) *glm::scale(glm::vec3(6.0f / 40)));
		}
		if (counter == 6) {
			uranusTranslate = glm::vec3(sunPos.x + 1400.0f * sinf(timeF / 20), sunPos.y, sunPos.z + 1400.0f * cosf(timeF / 20));
			obj->setMatrix(glm::translate(uranusTranslate) * planetRotation * glm::scale(glm::vec3(40.0f)));
		}
		if (counter == 7) {
			neptuneTranslate = glm::vec3(sunPos.x + -1700.0f * sinf(timeF / 22), sunPos.y, sunPos.z + -1700.0f * cosf(timeF / 22));
			obj->setMatrix(glm::translate(neptuneTranslate) * planetRotation * glm::scale(glm::vec3(39.0f)));
		}
		if (counter == 8) {
			mercury2Translate = glm::vec3(sunPos2.x + 170.0f * sinf(timeF / 8), sunPos2.y, sunPos2.z + 170.0f * cosf(timeF / 8));
			obj->setMatrix(glm::translate(mercury2Translate) * planetRotation * glm::scale(glm::vec3(20 * 0.48f)));
		}
		if (counter == 9) {
			venus2Translate = glm::vec3(sunPos2.x + -260.0f * sinf(timeF / 10), sunPos2.y, sunPos2.z + -260.0f * cosf(timeF / 10));
			obj->setMatrix(glm::translate(venus2Translate) * planetRotation * glm::scale(glm::vec3(15 * 1.21f)));
		}
		if (counter == 10) {
			earth2Translate = glm::vec3(sunPos2.x + 350.0f * sinf(timeF / 12), sunPos2.y, sunPos2.z + 350.0f * cosf(timeF / 12));
			obj->setMatrix(glm::translate(earth2Translate) * planetRotation * glm::scale(glm::vec3(15 * 1.27f)));
		}
		if (counter == 11) {
			mars2Translate = glm::vec3(sunPos2.x + -440.0f * sinf(timeF / 14), sunPos2.y, sunPos2.z + -440.0 * cosf(timeF / 14));
			obj->setMatrix(glm::translate(mars2Translate) * planetRotation * glm::scale(glm::vec3(20 * 0.68f)));
		}
		if (counter == 12) {
			jupiter2Translate = glm::vec3(sunPos2.x + 800.0f * sinf(timeF / 16), sunPos2.y, sunPos2.z + 800.0f * cosf(timeF / 16));
			obj->setMatrix(glm::translate(jupiter2Translate) * planetRotation * glm::scale(glm::vec3(7 * 7.1f)));
		}
		if (counter == 13) {
			saturn2Translate = glm::vec3(sunPos2.x + -1100.0f * sinf(timeF / 18), sunPos2.y, sunPos2.z + -1100.0f * cosf(timeF / 18));
			obj->setMatrix(glm::translate(saturn2Translate) * planetRotation * glm::rotate(glm::radians(90.0f), glm::vec3(1, 0, 0)) * glm::scale(glm::vec3(6.0f / 40)));
		}
		if (counter == 14) {
			uranus2Translate = glm::vec3(sunPos2.x + 1400.0f * sinf(timeF / 20), sunPos2.y, sunPos2.z + 1400.0f * cosf(timeF / 20));
			obj->setMatrix(glm::translate(uranus2Translate) * planetRotation * glm::scale(glm::vec3(40.0f)));
		}
		if (counter == 15) {
			neptune2Translate = glm::vec3(sunPos2.x + -1700.0f * sinf(timeF / 22), sunPos2.y, sunPos2.z + -1700.0f * cosf(timeF / 22));
			obj->setMatrix(glm::translate(neptune2Translate) * planetRotation * glm::scale(glm::vec3(39.0f)));
		}
		obj->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
		if (counter == 16 && mouseKeyDown) {
			obj->setMatrix(glm::translate(glm::vec3(cameraPos.x + (cameraDir.x * 0.5f), cameraPos.y + (cameraDir.y * 0.5f), cameraPos.z + (cameraDir.z * 0.5f))) * glm::mat4_cast(glm::inverse(rotation)) * glm::rotate(shipAngle, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::scale(glm::vec3(0.015f, 0.001f, 0.015f)));
			obj->draw(glm::vec3(1.0f), cameraPos, perspectiveMatrix, cameraMatrix);
		}
		if (counter == 17 && mouseKeyDown) {
			obj->setMatrix(glm::translate(glm::vec3(cameraPos.x + (cameraDir.x * 0.5f), cameraPos.y + (cameraDir.y * 0.5f), cameraPos.z + (cameraDir.z * 0.5f))) * glm::mat4_cast(glm::inverse(rotation)) * glm::rotate(shipAngle, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::scale(glm::vec3(0.001f, 0.015f, 0.001f)));
			obj->draw(glm::vec3(1.0f), cameraPos, perspectiveMatrix, cameraMatrix);
		}
		counter++;
	}
	counter = 0;
}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.1f, 0.3f, 1.0f);

	drawObjects();

	Skybox::renderSkybox(programSkybox, cameraMatrix, perspectiveMatrix);
	
	glutSwapBuffers();
}

void init()
{
	srand(time(0));
	glEnable(GL_DEPTH_TEST);
	programColor = shaderLoader.CreateProgram("shaders/shader_color.vert", "shaders/shader_color.frag");
	programTexture = shaderLoader.CreateProgram("shaders/shader_tex.vert", "shaders/shader_tex.frag");
	programSun = shaderLoader.CreateProgram("shaders/shader_sun.vert", "shaders/shader_sun.frag");
	programSight = shaderLoader.CreateProgram("shaders/shader_sight.vert", "shaders/shader_sight.frag");
	programBump = shaderLoader.CreateProgram("shaders/shader_bump.vert", "shaders/shader_bump.frag");
	programSkybox = shaderLoader.CreateProgram("shaders/shader_skybox.vert", "shaders/shader_skybox.frag");
	sphereModel = obj::loadModelFromFile("models/sphere.obj");
	shipModel = obj::loadModelFromFile("models/wraith.obj");
	planeModel = obj::loadModelFromFile("models/plane.obj");
	saturnModel = obj::loadModelFromFile("models/saturn.obj");
	ufoModel = obj::loadModelFromFile("models/ufo.obj");
	textureAsteroid = Core::LoadTexture("textures/asteroid.png");
	textureAsteroid_normals = Core::LoadTexture("textures/asteroid_normals.png");
	textureJupiter = Core::LoadTexture("textures/jupiter.png");
	textureMars = Core::LoadTexture("textures/mars.png");
	textureMercury = Core::LoadTexture("textures/mercury.png");
	textureVenus = Core::LoadTexture("textures/venus.png");
	textureEarth = Core::LoadTexture("textures/earth2.png");
	textureSaturn = Core::LoadTexture("textures/saturn.png");
	textureUranus = Core::LoadTexture("textures/uranus.png");
	textureNeptune = Core::LoadTexture("textures/neptune.png");
	textureSun = Core::LoadTexture("textures/sun.png");

	createObjects();
	appLoadingTime = glutGet(GLUT_ELAPSED_TIME)/1000.0f;

	Skybox::initSkybox();
}

void shutdown()
{
	shaderLoader.DeleteProgram(programColor);
	shaderLoader.DeleteProgram(programTexture);
	shaderLoader.DeleteProgram(programSkybox);
	shaderLoader.DeleteProgram(programSun);
}

void idle()
{
	glutPostRedisplay();
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 30);
	glutInitWindowSize(650, 650);
	glutCreateWindow("OpenGL Pierwszy Program");
	glewInit();

	init();
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(mouse);
	glutMouseFunc(mouseClick);
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);

	glutMainLoop();

	shutdown();

	return 0;
}
