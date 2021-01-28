#include "Object.h"

Object::Object()
{
}

void Object::draw(glm::vec3 color, glm::vec3 cameraPos, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix)
{
	glUseProgram(this->getProgram());
	glUniform3f(glGetUniformLocation(this->getProgram(), "objectColor"), color.x, color.y, color.z);
	//glUniform3f(glGetUniformLocation(program, "lightDir"), lightDir.x, lightDir.y, lightDir.z);
	glm::vec3 lightPos = this->getLightPos();
	glm::vec3 lightPos2 = this->getLightPos2();
	glUniform3f(glGetUniformLocation(this->getProgram(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(this->getProgram(), "lightPos2"), lightPos2.x, lightPos2.y, lightPos2.z);
	glUniform3f(glGetUniformLocation(this->getProgram(), "cameraPos"), cameraPos.x, cameraPos.y, cameraPos.z);
	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * this->getMatrix();
	glUniformMatrix4fv(glGetUniformLocation(this->getProgram(), "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(this->getProgram(), "modelMatrix"), 1, GL_FALSE, (float*)&this->getMatrix());
	Core::DrawModel(this->getModel());
	glUseProgram(0);
}


void Object::drawTexture(glm::vec3 cameraPos, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix)
{
	glUseProgram(this->getProgram());
	glm::vec3 lightPos = this->getLightPos();
	glm::vec3 lightPos2 = this->getLightPos2();
	glUniform3f(glGetUniformLocation(this->getProgram(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(this->getProgram(), "lightPos2"), lightPos2.x, lightPos2.y, lightPos2.z);
	Core::SetActiveTexture(this->getTexture(), "textureSampler", this->getProgram(), 0);
	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * this->getMatrix();
	glUniformMatrix4fv(glGetUniformLocation(this->getProgram(), "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)& transformation);
	glUniformMatrix4fv(glGetUniformLocation(this->getProgram(), "modelMatrix"), 1, GL_FALSE, (float*)& this->getMatrix());
	Core::DrawModel(this->getModel());
	glUseProgram(0);
}
