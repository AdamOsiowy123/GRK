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

using namespace std;
class Object
{
private:
	GLuint program;
	obj::Model model;
	glm::mat4 matrix;
	GLuint texture;
	glm::vec3 lightPos;
	glm::vec3 lightPos2;
public:
	static vector<Object*> objects;
	Object(GLuint program,obj::Model model,glm::mat4 matrix,GLuint texture,glm::vec3 lightPos,glm::vec3 lightPos2);
	obj::Model getModel() { return model; }
	glm::mat4 getMatrix() { return matrix; }
	void setMatrix(glm::mat4 matrix);
	void draw(glm::vec3 color,glm::vec3 cameraPos,glm::mat4 perspectiveMatrix,glm::mat4 cameraMatrix);
	void drawTexture(glm::vec3 cameraPos, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix);
};

