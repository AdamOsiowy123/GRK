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


Core::Shader_Loader shaderLoader;

obj::Model shipModel;
obj::Model sphereModel;

glm::vec3 cameraPos = glm::vec3(0, 0, 5);
glm::vec3 cameraDir; // Wektor "do przodu" kamery
glm::vec3 cameraSide; // Wektor "w bok" kamery
float cameraAngle = 0;

glm::mat4 cameraMatrix, perspectiveMatrix;

glm::vec3 lightDir = glm::normalize(glm::vec3(1.0f, -0.9f, -1.0f));

glm::vec3 sunPos = glm::vec3(0.0f, 0.0f, 10.0f);
glm::vec3 sunPos2 = glm::vec3(30.0f, -20.0f, -30.0f);
glm::vec3 sunColor = glm::vec3(1.0f, 0.5f, 0.2f);

glm::quat rotation = glm::quat(1, 0, 0, 0);

GLuint textureAsteroid;
GLuint textureAsteroid_normals;
GLuint textureJupiter;
GLuint textureMars;
GLuint textureVenus;
GLuint textureMercury;

GLuint textureId;

glm::vec3 wspolrzedne[400];
glm::mat4 scale[400];
int roznicaX;
int roznicaY;
int ostatniX;
int ostatniY;
int roznicaZ;

void keyboard(unsigned char key, int x, int y)
{
	
	float angleSpeed = 0.1f;
	float moveSpeed = 0.1f;
	switch(key)
	{
	case 'z': roznicaZ = -20.0f; break;
	case 'x': roznicaZ = 20.0f; break;
	case 'w': cameraPos += cameraDir * moveSpeed; break;
	case 's': cameraPos -= cameraDir * moveSpeed; break;
	case 'd': cameraPos += cameraSide * moveSpeed; break;
	case 'a': cameraPos -= cameraSide * moveSpeed; break;
	}
}

void mouse(int x, int y)
{
	roznicaX = x - ostatniX;
	roznicaY = y - ostatniY;
	ostatniX = x;
	ostatniY = y;
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
	for (int i = 0; i < 300; i++) {
		wspolrzedne[i] = glm::ballRand(100.0f);
	}
	for (int i = 0; i < 50; i++) {
		scale[i] = glm::scale(glm::vec3(rand() % 5 * 1.0f));
	}
	ostatniX = 300;
	ostatniY = 300;

	std::shared_ptr<Ship>  ship = Ship::create(programColor, &shipModel, sunPos, sunPos2, glm::vec3(0.6f));

	std::shared_ptr<Sun> sun1 = Sun::create(programSun, &sphereModel, glm::translate(sunPos) * glm::scale(glm::vec3(2.0f)),sunPos,sunPos2,sunColor);
	std::shared_ptr<Sun> sun2 = Sun::create(programSun, &sphereModel, glm::translate(sunPos2) * glm::scale(glm::vec3(2.0f)), sunPos, sunPos2, sunColor);

	std::shared_ptr<Asteroid> asteroid = Asteroid::create(programTexture, &sphereModel, glm::translate(glm::vec3(0, 0, 0)),textureAsteroid,sunPos,sunPos2);

	for (int i = 0; i < 300; i++) {
		if (i % 4 == 0) {
			textureId = textureJupiter;
		}
		else if (i % 4 == 1) {
			textureId = textureMercury;
		}
		else if (i % 4 == 2) {
			textureId = textureMars;
		}
		else if (i % 4 == 3) {
			textureId = textureVenus;
		}
		std::shared_ptr<Planet> planet = Planet::create(programTexture, &sphereModel, glm::translate(wspolrzedne[i]) * scale[i % 50],textureId,sunPos,sunPos2);
	}

}

void drawObjects() {
	cameraMatrix = createCameraMatrix();
	perspectiveMatrix = Core::createPerspectiveMatrix();
	glm::mat4 shipInitialTransformation = glm::translate(glm::vec3(0, -0.25f, 0)) * glm::rotate(glm::radians(180.0f), glm::vec3(0, 1, 0)) * glm::scale(glm::vec3(0.25f));
	glm::mat4 shipModelMatrix = glm::translate(cameraPos + cameraDir * 0.5f) * glm::mat4_cast(glm::inverse(rotation)) * shipInitialTransformation;
	//ship.setMatrix(shipModelMatrix);
	for (auto obj : Ship::ship_objects) {
		obj->setMatrix(shipModelMatrix);
		obj->draw(obj->getColor(), cameraPos, perspectiveMatrix, cameraMatrix);
	}
	for (auto obj : Sun::sun_objects) {
		obj->draw(obj->getColor(), cameraPos, perspectiveMatrix, cameraMatrix);
	}
	for (auto obj : Asteroid::asteroid_objects) {
		obj->drawTexture(cameraPos,perspectiveMatrix,cameraMatrix);
	}
	for (auto obj : Planet::planet_objects) {
		obj->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	}
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
	sphereModel = obj::loadModelFromFile("models/sphere.obj");
	shipModel = obj::loadModelFromFile("models/spaceship.obj");
	textureAsteroid = Core::LoadTexture("textures/asteroid.png");
	textureAsteroid_normals = Core::LoadTexture("textures/asteroid_normals.png");
	textureJupiter = Core::LoadTexture("textures/jupiter.png");
	textureMars = Core::LoadTexture("textures/mars.png");
	textureMercury = Core::LoadTexture("textures/mercury.png");
	textureVenus = Core::LoadTexture("textures/venus.png");
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
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);

	glutMainLoop();

	shutdown();

	return 0;
}
