#include "Asteroid.h"

std::vector<std::shared_ptr<Asteroid>> Asteroid::asteroid_objects;

Asteroid::Asteroid() {

}

Asteroid::Asteroid(GLuint program, obj::Model* model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2)
{
	this->program = program;
	this->model = model;
	this->matrix = matrix;
	this->texture = texture;
	this->lightPos = lightPos;
	this->lightPos2 = lightPos2;
}

std::shared_ptr<Asteroid> Asteroid::create()
{
	shared_ptr<Asteroid> asteroid = shared_ptr<Asteroid>(new Asteroid());
	asteroid_objects.push_back(asteroid);
	return asteroid;
}

std::shared_ptr<Asteroid> Asteroid::create(GLuint program, obj::Model* model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2)
{
	shared_ptr<Asteroid> asteroid = shared_ptr<Asteroid>(new Asteroid(program,model,matrix,texture,lightPos,lightPos2));
	asteroid_objects.push_back(asteroid);
	return asteroid;
}