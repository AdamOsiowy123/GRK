#pragma once
#include "Object.h"
class Planet :
    public Object
{
public:
    static std::vector<Planet*> planet_objects;
    Planet(GLuint program, obj::Model model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2);
};

