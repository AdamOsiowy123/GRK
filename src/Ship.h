#pragma once
#include "Object.h"
#include <memory>
class Ship :
    public Object
{
private:
    glm::vec3 color;
    Ship();
    Ship(GLuint program, obj::Model* model, glm::vec3 lightPos, glm::vec3 lightPos2, glm::vec3 color);
    Ship(GLuint program, obj::Model* model, glm::mat4 matrix, glm::vec3 lightPos, glm::vec3 lightPos2, glm::vec3 color);
public:
    static std::shared_ptr<Ship> create();
    static std::shared_ptr<Ship> create(GLuint program, obj::Model* model, glm::vec3 lightPos, glm::vec3 lightPos2, glm::vec3 color);
    static std::shared_ptr<Ship> create(GLuint program, obj::Model* model, glm::mat4 matrix, glm::vec3 lightPos, glm::vec3 lightPos2, glm::vec3 color);
    static std::vector<std::shared_ptr<Ship>> ship_objects;
    void setMatrix(glm::mat4 matrix);
    glm::vec3 getColor() { return color; }
};

