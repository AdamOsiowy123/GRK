#include "Asteroid.h"

std::vector<Asteroid*> Asteroid::asteroid_objects;

Asteroid::Asteroid() {

}

Asteroid::Asteroid(GLuint program, obj::Model* model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2)
{
	std::cout <<"asteroida: "<< model << std::endl;
	this->program = program;
	this->model = model;
	this->matrix = matrix;
	this->texture = texture;
	this->lightPos = lightPos;
	this->lightPos2 = lightPos2;
}
void Asteroid::addToStaticVector() {
	std::cout << "asteroida static: " << this->model << std::endl;
	Asteroid::asteroid_objects.push_back(this);
}
void Asteroid::draw(glm::vec3 color, glm::vec3 cameraPos, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix)
{
	std::cout << "draw" << std::endl;
	glUseProgram(this->program);
	std::cout << "1" << std::endl;
	glUniform3f(glGetUniformLocation(this->program, "objectColor"), color.x, color.y, color.z);
	//glUniform3f(glGetUniformLocation(program, "lightDir"), lightDir.x, lightDir.y, lightDir.z);
	glUniform3f(glGetUniformLocation(this->program, "lightPos"), this->lightPos.x, this->lightPos.y, this->lightPos.z);
	glUniform3f(glGetUniformLocation(this->program, "lightPos2"), this->lightPos2.x, this->lightPos2.y, this->lightPos2.z);
	glUniform3f(glGetUniformLocation(this->program, "cameraPos"), cameraPos.x, cameraPos.y, cameraPos.z);
	std::cout << "2" << std::endl;
	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * this->matrix;
	glUniformMatrix4fv(glGetUniformLocation(this->program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(this->program, "modelMatrix"), 1, GL_FALSE, (float*)&this->matrix);
	std::cout << "3" << std::endl;
	Core::DrawModel(this->model);
	std::cout << "4" << std::endl;
	glUseProgram(0);
	std::cout << "5" << std::endl;
}

void Asteroid::drawTexture(glm::vec3 cameraPos, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix)
{
	std::cout << "draw texture" << std::endl;
	glUseProgram(this->program);
	std::cout << "1" << std::endl;
	glUniform3f(glGetUniformLocation(this->program, "lightPos"), this->lightPos.x, this->lightPos.y, this->lightPos.z);
	glUniform3f(glGetUniformLocation(this->program, "lightPos2"), this->lightPos2.x, this->lightPos2.y, this->lightPos2.z);
	Core::SetActiveTexture(this->texture, "textureSampler", this->program, 0);
	std::cout << "2" << std::endl;
	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * this->matrix;
	glUniformMatrix4fv(glGetUniformLocation(this->program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(this->program, "modelMatrix"), 1, GL_FALSE, (float*)&this->matrix);
	std::cout << "3" << std::endl;
	Core::DrawModel(this->model);
	std::cout << "4" << std::endl;
	glUseProgram(0);
}