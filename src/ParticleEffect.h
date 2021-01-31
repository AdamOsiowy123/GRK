#pragma once
#include "glew.h"
#include "freeglut.h"
#include "glm.hpp"
#include "ext.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include "Texture.h"
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
#include <string_view>
#include <cstdlib>
#include <ctime>

struct Particle {
    glm::vec3 Position, Velocity;
    float Age;
    float Life;

    Particle(glm::vec3 pos) : Position(glm::vec3(pos.x + (rand() %5 ) / 10.0f, pos.y + (rand() % 5) / 10.0f, pos.z + (rand() % 5) / 10.0f)), Velocity(glm::vec3(((rand() % 5) -10) / 10.0f, ((rand() % 5) -10)/ 10.0f, ((rand() % 5) -10) / 10.0f)), Age(0.0f), Life(1.0f) { }
    bool operator<(Particle& that) {
        // old particles drawn first
        return this->Age > that.Age;
    }
};

class ParticleEffect
{
public:
    ParticleEffect(GLuint shader, unsigned int amount, float delta, std::vector<GLuint> textures,glm::vec3 position);
    void simulate();
    void deactivate();
    void sendProjectionToShader(glm::mat4 persp, glm::mat4 camera);
private:
    GLuint shader;
    std::vector<Particle> particles;
    std::vector<GLuint> textures;
    glm::vec3 position;
    unsigned int VAO;
    unsigned int amount;
    bool active;
    float delta;
    void init();
    void draw();
    void update();
    void sortParticles();
    void deleteDeadParticles();
    GLuint selectTexture(float age);
};

