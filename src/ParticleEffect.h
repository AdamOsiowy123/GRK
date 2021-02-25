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
#include <ctime>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <random>


struct Particle {
    glm::vec3 Position, Velocity;
    float Age;
    float Life;
	Particle(glm::vec3 pos, glm::vec3 vel) : Position(glm::vec3(pos.x, pos.y, pos.z)), Velocity(glm::vec3(vel.x, vel.y, vel.z)), Age(0.0f), Life(1.0f) { }
    bool operator<(Particle& that) {
        // old particles drawn first
        return this->Age > that.Age;
    }
};

class ParticleEffect
{
public:
    ParticleEffect(GLuint shader, unsigned int amount, float delta, std::vector<GLuint> textures,glm::vec3 position, glm::vec3 velocity);
    void simulate();
    void sendProjectionToShader(glm::mat4 persp, glm::mat4 camera);
    bool isActive();
    glm::vec3 getPosition();
private:
    GLuint shader;
    std::vector<Particle> particles;
    std::vector<GLuint> textures;
    glm::vec3 position, velocity;
    unsigned int VAO;
    unsigned int amount;
    bool active;
    float delta;
    void init();
    void draw();
    void update();
    void deactivate();
    void sortParticles();
    void deleteDeadParticles();
    GLuint selectTexture(float age);
};

