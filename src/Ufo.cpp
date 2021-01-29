#include "Ufo.h"

std::vector<std::shared_ptr<Ufo>> Ufo::ufo_objects;

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


std::shared_ptr<Ufo> Ufo::create()
{
	shared_ptr<Ufo> ufo = shared_ptr<Ufo>(new Ufo());
	ufo_objects.push_back(ufo);
	return ufo;
}
std::shared_ptr<Ufo> Ufo::create(GLuint program, obj::Model* model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2)
{
	shared_ptr<Ufo> ufo = shared_ptr<Ufo>(new Ufo(program, model, matrix, texture, lightPos, lightPos2));
	ufo_objects.push_back(ufo);
	return ufo;
}


void Ufo::setMatrix(glm::mat4 matrix)
{
	this->matrix = matrix;
}