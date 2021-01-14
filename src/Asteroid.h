#pragma once
#include "Object.h"
class Asteroid :
    public Object
{
public:
    static std::vector<Asteroid*> asteroid_objects;
    Asteroid(GLuint program, obj::Model model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2);
};

