#include "Planet.h"

std::vector<std::shared_ptr<Planet>> Planet::planet_objects;

Planet::Planet()
{
}

Planet::Planet(GLuint program, obj::Model* model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2)
{
	this->program = program;
	this->model = model;
	this->matrix = matrix;
	this->texture = texture;
	this->lightPos = lightPos;
	this->lightPos2 = lightPos2;
}

Planet::Planet(GLuint program, obj::Model* model, glm::mat4 matrix, glm::vec3 lightPos, glm::vec3 lightPos2)
{
	this->program = program;
	this->model = model;
	this->matrix = matrix;
	this->lightPos = lightPos;
	this->lightPos2 = lightPos2;
}

std::shared_ptr<Planet> Planet::create()
{
	shared_ptr<Planet> planet = shared_ptr<Planet>(new Planet());
	planet_objects.push_back(planet);
	return planet;
}
std::shared_ptr<Planet> Planet::create(GLuint program, obj::Model* model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2)
{
	shared_ptr<Planet> planet = shared_ptr<Planet>(new Planet(program,model,matrix,texture,lightPos,lightPos2));
	planet_objects.push_back(planet);
	return planet;
}

std::shared_ptr<Planet> Planet::create(GLuint program, obj::Model* model, glm::mat4 matrix, glm::vec3 lightPos, glm::vec3 lightPos2)
{
	shared_ptr<Planet> planet = shared_ptr<Planet>(new Planet(program, model, matrix, lightPos, lightPos2));
	planet_objects.push_back(planet);
	return planet;
}

void Planet::setMatrix(glm::mat4 matrix)
{
	this->matrix = matrix;
}