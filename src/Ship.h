#pragma once
#include "Object.h"
#include <memory>
class Ship :
    public Object
{
private:
    glm::vec3 color;
public:
    Ship();
    Ship(GLuint program, obj::Model* model, glm::vec3 lightPos, glm::vec3 lightPos2, glm::vec3 color);
    void setMatrix(glm::mat4 matrix);
    glm::vec3 getColor() { return color; }
};

