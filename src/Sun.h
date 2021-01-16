#pragma once
#include "Object.h"
#include <memory>
class Sun :
    public Object
{
private:
    glm::vec3 color;
    Sun();
    Sun(GLuint program, obj::Model* model, glm::mat4 matrix, glm::vec3 lightPos, glm::vec3 lightPos2, glm::vec3 color);
public:
    static std::vector<std::shared_ptr<Sun>> sun_objects;
    static std::shared_ptr<Sun> create();
    static std::shared_ptr<Sun> create(GLuint program, obj::Model* model, glm::mat4 matrix, glm::vec3 lightPos, glm::vec3 lightPos2, glm::vec3 color);
    glm::vec3 getColor() { return color; }
};

