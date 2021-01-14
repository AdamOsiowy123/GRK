#include "Sun.h"

Sun::Sun(GLuint program, obj::Model model, glm::mat4 matrix, glm::vec3 lightPos, glm::vec3 lightPos2)
{
	this->program = program;
	this->model = model;
	this->matrix = matrix;
	this->lightPos = lightPos;
	this->lightPos2 = lightPos2;
	Sun::sun_objects.push_back(this);
}
std::vector<Sun*> Sun::sun_objects;