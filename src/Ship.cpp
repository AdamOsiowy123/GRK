#include "Ship.h"

Ship::Ship()
{
}

Ship::Ship(GLuint program, obj::Model* model, glm::vec3 lightPos, glm::vec3 lightPos2, glm::vec3 color)
{
	this->program = program;
	this->model = model;
	this->lightPos = lightPos;
	this->lightPos2 = lightPos2;
	this->color = color;
}

void Ship::setMatrix(glm::mat4 matrix)
{
	this->matrix = matrix;
}
