#include "Ship.h"

std::vector<std::shared_ptr<Ship>> Ship::ship_objects;

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

Ship::Ship(GLuint program, obj::Model* model, glm::mat4 matrix, glm::vec3 lightPos, glm::vec3 lightPos2,glm::vec3 color)
{
	this->program = program;
	this->model = model;
	this->matrix = matrix;
	this->lightPos = lightPos;
	this->lightPos2 = lightPos2;
	this->color = color;
}

std::shared_ptr<Ship> Ship::create()
{
	shared_ptr<Ship> ship = shared_ptr<Ship>(new Ship());
	ship_objects.push_back(ship);
	return ship;
}

std::shared_ptr<Ship> Ship::create(GLuint program, obj::Model* model, glm::vec3 lightPos, glm::vec3 lightPos2, glm::vec3 color)
{
	shared_ptr<Ship> ship = shared_ptr<Ship>(new Ship(program, model, lightPos, lightPos2, color));
	ship_objects.push_back(ship);
	return ship;
}

std::shared_ptr<Ship> Ship::create(GLuint program, obj::Model* model, glm::mat4 matrix, glm::vec3 lightPos, glm::vec3 lightPos2, glm::vec3 color)
{
	shared_ptr<Ship> ship = shared_ptr<Ship>(new Ship(program,model,matrix,lightPos,lightPos2,color));
	ship_objects.push_back(ship);
	return ship;
}

void Ship::setMatrix(glm::mat4 matrix)
{
	this->matrix = matrix;
}
