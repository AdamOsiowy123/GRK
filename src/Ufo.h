#pragma once
#include "Object.h"
#include <memory>
class Ufo :
	public Object
{
private:
	Ufo();
	Ufo(GLuint program, obj::Model* model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2);
public:
	static std::vector<std::shared_ptr<Ufo>> ufo_objects;
	static std::shared_ptr<Ufo> create();
	static std::shared_ptr<Ufo> create(GLuint program, obj::Model* model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2);
	void Ufo::setMatrix(glm::mat4 matrix);
};

