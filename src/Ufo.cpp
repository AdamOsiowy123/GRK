#include "Ufo.h"

Ufo::Ufo()
{
}

Ufo::Ufo(GLuint program, obj::Model* model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2)
{
	this->program = program;
	this->model = model;
	this->matrix = matrix;
	this->texture = texture;
	this->lightPos = lightPos;
	this->lightPos2 = lightPos2;
}

void Ufo::setMatrix(glm::mat4 matrix)
{
	this->matrix = matrix;
}