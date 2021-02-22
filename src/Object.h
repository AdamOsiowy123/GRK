#pragma once
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
//#include "Physics.h"

using namespace std;
class Object
{
protected:
	GLuint program;
	obj::Model* model;
	glm::mat4 matrix;
	GLuint texture;
	glm::vec3 lightPos;
	glm::vec3 lightPos2;
	//PxMaterial* material;
	//PxRigidDynamic* body;
	//PxShape* shape;
	//Physics* scene;
	//glm::vec3 translation;
	//glm::vec3 size;
public:
	Object();
	void draw(glm::vec3 color, glm::vec3 cameraPos, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix);
	void drawTexture(glm::vec3 cameraPos, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix);
	GLuint getProgram() { return program; }
	obj::Model* getModel() { return model; }
	glm::mat4 getMatrix() { return matrix; }
	GLuint getTexture() { return texture; }
	glm::vec3 getLightPos() { return lightPos; }
	glm::vec3 getLightPos2() { return lightPos2; }
	//void setTranslation(glm::vec3 translation);
	//glm::vec3 getTranslation() { return translation; }
	//void setSize(glm::vec3 size);
	//glm::vec3 getSize() { return size; }
	//PxRigidDynamic* getBody() { return body; }
};

