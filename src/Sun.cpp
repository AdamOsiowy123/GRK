#include "Sun.h"

std::vector<std::shared_ptr<Sun>> Sun::sun_objects;

Sun::Sun()
{
}

Sun::Sun(GLuint program, obj::Model* model, glm::mat4 matrix, glm::vec3 lightPos, glm::vec3 lightPos2, GLuint texture)
{
	this->program = program;
	this->model = model;
	this->matrix = matrix;
	this->lightPos = lightPos;
	this->lightPos2 = lightPos2;
	this->texture = texture;
}

std::shared_ptr<Sun> Sun::create()
{
	shared_ptr<Sun> sun = shared_ptr<Sun>(new Sun());
	sun_objects.push_back(sun);
	return sun;
}

std::shared_ptr<Sun> Sun::create(GLuint program, obj::Model* model, glm::mat4 matrix, glm::vec3 lightPos, glm::vec3 lightPos2, GLuint texture)
{
	shared_ptr<Sun> sun = shared_ptr<Sun>(new Sun(program,model,matrix,lightPos,lightPos2,texture));
	sun_objects.push_back(sun);
	return sun;
}