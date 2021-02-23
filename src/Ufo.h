#pragma once
#include "Object.h"
#include <memory>
class Ufo :
	public Object
{
private:
	Ufo();
public:
	Ufo(GLuint program, obj::Model* model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2);
	void Ufo::setMatrix(glm::mat4 matrix);
};

