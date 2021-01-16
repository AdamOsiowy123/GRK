#pragma once
#include "Object.h"
#include <memory>
class Planet :
    public Object
{
private:
    Planet();
    Planet(GLuint program, obj::Model* model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2);
public:
    static std::vector<std::shared_ptr<Planet>> planet_objects;
    static std::shared_ptr<Planet> create();
    static std::shared_ptr<Planet> create(GLuint program, obj::Model* model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2);
};

