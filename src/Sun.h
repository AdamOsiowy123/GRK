#pragma once
#include "Object.h"
class Sun :
    public Object
{
protected:
    glm::vec3 color;
public:
    Sun();
    static std::vector<Sun*> sun_objects;
    Sun(GLuint program, obj::Model* model, glm::mat4 matrix, glm::vec3 lightPos, glm::vec3 lightPos2,glm::vec3 color);
    glm::vec3 getColor() { return color; }
    void addToStaticVector();
    void draw(glm::vec3 color, glm::vec3 cameraPos, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix);
    void drawTexture(glm::vec3 cameraPos, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix);
};

