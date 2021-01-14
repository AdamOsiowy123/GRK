#include "Planet.h"

Planet::Planet(GLuint program, obj::Model model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2)
{
	this->program = program;
	this->model = model;
	this->matrix = matrix;
	this->texture = texture;
	this->lightPos = lightPos;
	this->lightPos2 = lightPos2;
	Planet::planet_objects.push_back(this);
}
