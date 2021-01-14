#pragma once
#include "Object.h"
class Planet :
    public Object
{
public:
    Planet();
    static std::vector<Planet*> planet_objects;
    Planet(GLuint program, obj::Model* model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2);
    void addToStaticVector();
    void draw(glm::vec3 color, glm::vec3 cameraPos, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix);
    void drawTexture(glm::vec3 cameraPos, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix);
};

