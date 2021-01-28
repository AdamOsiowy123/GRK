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

void Asteroid::drawTexture(glm::vec3 cameraPos, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix)
{
	glUseProgram(this->getProgram());
	glm::vec3 lightPos = this->getLightPos();
	glm::vec3 lightPos2 = this->getLightPos2();
	glUniform3f(glGetUniformLocation(this->getProgram(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(this->getProgram(), "lightPos2"), lightPos2.x, lightPos2.y, lightPos2.z);
	glUniform3f(glGetUniformLocation(this->getProgram(), "cameraPos"), cameraPos.x, cameraPos.y, cameraPos.z);
	Core::SetActiveTexture(this->getTexture(), "textureSampler", this->getProgram(), 0);
	Core::SetActiveTexture(this->getNormal(), "normalSampler", this->getProgram(), 1);
	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * this->getMatrix();
	glUniformMatrix4fv(glGetUniformLocation(this->getProgram(), "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)& transformation);
	glUniformMatrix4fv(glGetUniformLocation(this->getProgram(), "modelMatrix"), 1, GL_FALSE, (float*)& this->getMatrix());
	Core::DrawModel(this->getModel());
	glUseProgram(0);
}

void Asteroid::setNormal(GLuint normal)
{
	this->normal = normal;
}

GLuint Asteroid::getNormal()
{
	return this->normal;
}
