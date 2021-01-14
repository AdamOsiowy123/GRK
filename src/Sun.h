#pragma once
#include "Object.h"
class Sun :
    public Object
{
public:
    static std::vector<Sun*> sun_objects;
    Sun(GLuint program, obj::Model model, glm::mat4 matrix, glm::vec3 lightPos, glm::vec3 lightPos2);
};

