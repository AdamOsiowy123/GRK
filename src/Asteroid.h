#pragma once
#include "Object.h"
#include <memory>
class Asteroid :
    public Object
{
private:
    Asteroid();
    Asteroid(GLuint program, obj::Model* model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2);
    //Asteroid(GLuint program, obj::Model* model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2, Physics* scene);
	GLuint normal;
public:
    static std::vector<std::shared_ptr<Asteroid>> asteroid_objects;
    static std::shared_ptr<Asteroid> create();
    static std::shared_ptr<Asteroid> create(GLuint program, obj::Model* model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2);
    //static std::shared_ptr<Asteroid> create(GLuint program, obj::Model* model, glm::mat4 matrix, GLuint texture, glm::vec3 lightPos, glm::vec3 lightPos2, Physics* scene);

	void drawTexture(glm::vec3 cameraPos, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix);

	void setNormal(GLuint normal);
	GLuint getNormal();
};

