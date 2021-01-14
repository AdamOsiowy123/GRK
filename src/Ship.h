#pragma once
#include "Object.h"
class Ship :
    public Object
{
public:
    static std::vector<Ship*> ship_objects;
    Ship(GLuint program, obj::Model model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2);
};

