#include "Ship.h"

Ship::Ship(GLuint program, obj::Model model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2)
{
	this->program = program;
	this->model = model;
	this->matrix = matrix;
	this->texture = texture;
	this->lightPos = lightPos;
	this->lightPos2 = lightPos2;
	Ship::ship_objects.push_back(this);
}
std::vector<Ship*> Ship::ship_objects;