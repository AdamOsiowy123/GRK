#include "glew.h"
#include "freeglut.h"
#include "glm.hpp"
#include "ext.hpp"
#include <iostream>
#include <cmath>
#include <vector>

#include "Shader_Loader.h"
#include "Render_Utils.h"
#include "Camera.h"
#include "Texture.h"
#include "Asteroid.h"
#include "Planet.h"
#include "Sun.h"
#include "Ship.h"
#include <memory>

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

GLuint textureId;

glm::vec3 wspolrzedne[400];
int roznicaX;
int roznicaY;
int ostatniX = 300;
int ostatniY = 300;
int roznicaZ;
int counter = 0;

bool mouseKeyDown = false;

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
	std::cout << mouseKeyDown << std::endl;
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

	std::shared_ptr<Planet> gunSight1 = Planet::create(programSight, &planeModel, planetDefaultMatrix, sunPos, sunPos2);
	std::shared_ptr<Planet> gunSight2 = Planet::create(programSight, &planeModel, planetDefaultMatrix, sunPos, sunPos2);
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
	shipModelMatrix = glm::translate(cameraPos + cameraDir * 0.5f) * glm::mat4_cast(glm::inverse(rotation)) * shipInitialTransformation;
	glm::mat4 planetRotation = glm::rotate(3.14f / 2.f * timeF / 2, glm::vec3(0.0f, 1.0f, 0.0f));

	for (auto obj : Ship::ship_objects) {
		obj->setMatrix(shipModelMatrix);
		obj->draw(obj->getColor(), cameraPos, perspectiveMatrix, cameraMatrix);
	}
	for (auto obj : Sun::sun_objects) {
		obj->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	}
	for (auto obj : Asteroid::asteroid_objects) {
		obj->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	}
	for (auto obj : Planet::planet_objects) {
		if (counter == 0) {
			obj->setMatrix(glm::translate(glm::vec3(sunPos.x + 170.0f * sinf(timeF/8), sunPos.y, sunPos.z + 170.0f * cosf(timeF/8))) * planetRotation * glm::scale(glm::vec3(20 * 0.48f)));
		}
		if (counter == 1) {
			obj->setMatrix(glm::translate(glm::vec3(sunPos.x + -260.0f * sinf(timeF / 10), sunPos.y, sunPos.z + -260.0f * cosf(timeF / 10))) * planetRotation * glm::scale(glm::vec3(15 * 1.21f)));
		}
		if (counter == 2) {
			obj->setMatrix(glm::translate(glm::vec3(sunPos.x + 350.0f * sinf(timeF / 12), sunPos.y, sunPos.z + 350.0f * cosf(timeF / 12))) * planetRotation * glm::scale(glm::vec3(15 * 1.27f)));
		}
		if (counter == 3) {
			obj->setMatrix(glm::translate(glm::vec3(sunPos.x + -440.0f * sinf(timeF / 14), sunPos.y, sunPos.z + -440.0 * cosf(timeF / 14))) * planetRotation * glm::scale(glm::vec3(20 * 0.68f)));
		}
		if (counter == 4) {
			obj->setMatrix(glm::translate(glm::vec3(sunPos.x + 800.0f * sinf(timeF / 16), sunPos.y, sunPos.z + 800.0f * cosf(timeF / 16))) * planetRotation * glm::scale(glm::vec3(7 * 7.1f)));
		}
		if (counter == 5) {
			obj->setMatrix(glm::translate(glm::vec3(sunPos.x + -1100.0f * sinf(timeF / 18), sunPos.y, sunPos.z + -1100.0f * cosf(timeF / 18))) * planetRotation * glm::rotate(glm::radians(90.0f), glm::vec3(1, 0, 0)) *glm::scale(glm::vec3(6.0f / 40)));
		}
		if (counter == 6) {
			obj->setMatrix(glm::translate(glm::vec3(sunPos.x + 1400.0f * sinf(timeF / 20), sunPos.y, sunPos.z + 1400.0f * cosf(timeF / 20))) * planetRotation * glm::scale(glm::vec3(40.0f)));
		}
		if (counter == 7) {
			obj->setMatrix(glm::translate(glm::vec3(sunPos.x + -1700.0f * sinf(timeF / 22), sunPos.y, sunPos.z + -1700.0f * cosf(timeF / 22))) * planetRotation * glm::scale(glm::vec3(39.0f)));
		}
		if (counter == 8) {
			obj->setMatrix(glm::translate(glm::vec3(sunPos2.x + 170.0f * sinf(timeF / 8), sunPos2.y, sunPos2.z + 170.0f * cosf(timeF / 8))) * planetRotation * glm::scale(glm::vec3(20 * 0.48f)));
		}
		if (counter == 9) {
			obj->setMatrix(glm::translate(glm::vec3(sunPos2.x + -260.0f * sinf(timeF / 10), sunPos2.y, sunPos2.z + -260.0f * cosf(timeF / 10))) * planetRotation * glm::scale(glm::vec3(15 * 1.21f)));
		}
		if (counter == 10) {
			obj->setMatrix(glm::translate(glm::vec3(sunPos2.x + 350.0f * sinf(timeF / 12), sunPos2.y, sunPos2.z + 350.0f * cosf(timeF / 12))) * planetRotation * glm::scale(glm::vec3(15 * 1.27f)));
		}
		if (counter == 11) {
			obj->setMatrix(glm::translate(glm::vec3(sunPos2.x + -440.0f * sinf(timeF / 14), sunPos2.y, sunPos2.z + -440.0 * cosf(timeF / 14))) * planetRotation * glm::scale(glm::vec3(20 * 0.68f)));
		}
		if (counter == 12) {
			obj->setMatrix(glm::translate(glm::vec3(sunPos2.x + 800.0f * sinf(timeF / 16), sunPos2.y, sunPos2.z + 800.0f * cosf(timeF / 16))) * planetRotation * glm::scale(glm::vec3(7 * 7.1f)));
		}
		if (counter == 13) {
			obj->setMatrix(glm::translate(glm::vec3(sunPos2.x + -1100.0f * sinf(timeF / 18), sunPos2.y, sunPos2.z + -1100.0f * cosf(timeF / 18))) * planetRotation * glm::rotate(glm::radians(90.0f), glm::vec3(1, 0, 0)) * glm::scale(glm::vec3(6.0f / 40)));
		}
		if (counter == 14) {
			obj->setMatrix(glm::translate(glm::vec3(sunPos2.x + 1400.0f * sinf(timeF / 20), sunPos2.y, sunPos2.z + 1400.0f * cosf(timeF / 20))) * planetRotation * glm::scale(glm::vec3(40.0f)));
		}
		if (counter == 15) {
			obj->setMatrix(glm::translate(glm::vec3(sunPos2.x + -1700.0f * sinf(timeF / 22), sunPos2.y, sunPos2.z + -1700.0f * cosf(timeF / 22))) * planetRotation * glm::scale(glm::vec3(39.0f)));
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
	sphereModel = obj::loadModelFromFile("models/sphere.obj");
	shipModel = obj::loadModelFromFile("models/wraith.obj");
	planeModel = obj::loadModelFromFile("models/plane.obj");
	saturnModel = obj::loadModelFromFile("models/saturn.obj");
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
	
}

void shutdown()
{
	shaderLoader.DeleteProgram(programColor);
	shaderLoader.DeleteProgram(programTexture);
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
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(600, 600);
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
