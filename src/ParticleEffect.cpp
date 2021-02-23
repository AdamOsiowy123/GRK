#include "ParticleEffect.h"
#include <random>

ParticleEffect::ParticleEffect(GLuint shader, unsigned int amount, float delta, std::vector<GLuint> textures,glm::vec3 position, glm::vec3 velocity)
{
	this->shader = shader;
	this->amount = amount;
	this->delta = delta;
	this->active = true;
	this->textures = textures;
    this->position = position;
	this->velocity = velocity;
	this->init();
}

void ParticleEffect::simulate()
{
    if (this->active) {
        update();
        deleteDeadParticles();
        sortParticles();
        draw();
    }
}

void ParticleEffect::init()
{
    srand(time(NULL));

    unsigned int VBO;
    float particle_quad[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(this->VAO);
    // fill billboard buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
    // set billboard attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glm::vec3 pos;
    for (unsigned int i = 0; i < this->amount; ++i) {
        pos = this->position + glm::vec3(rand()%10,rand()%10,rand()%10);
        this->particles.push_back(Particle(pos, this->velocity));
    }
}

void ParticleEffect::draw()
{
    glUseProgram(this->shader);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (Particle p : this->particles)
    {
        if (p.Life > 0.0f)
        {
            glUniform3f(glGetUniformLocation(this->shader, "particlePosition"), p.Position.x, p.Position.y,p.Position.z);
            //std::cout << "x:"<< p.Position.x << " y:" << p.Position.y << " z:" << p.Position.z << std::endl;
            glBindTexture(GL_TEXTURE_2D, selectTexture(p.Age));
            glBindVertexArray(this->VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    glDisable(GL_BLEND);
    glUseProgram(0);
}

void ParticleEffect::update()
{
    for (unsigned int i = 0; i < this->particles.size(); ++i)
    {
        Particle& p = this->particles[i];
        p.Life -= this->delta; 
        p.Age += (this->delta * (rand()%3 + 1));
        //p.Age += 0.015625f;
        p.Position -= p.Velocity * this->delta;
    }
}

void ParticleEffect::deactivate()
{
	this->active = false;
}

void ParticleEffect::sortParticles()
{
    if (this->particles.size() > 0) {
        std::sort(&particles[0], &particles[this->particles.size()-1]);
    }
}

void ParticleEffect::deleteDeadParticles()
{   
    if (this->particles.size() == 0) {
        this->deactivate();
    }
    else {
        std::vector<Particle> copy;
        for (auto p : this->particles) {
            if (p.Life >= 0 && p.Age <= 1.0f) {
                copy.push_back(p);
            }
        }
        this->particles = copy;
    }
}

void ParticleEffect::sendProjectionToShader(glm::mat4 persp, glm::mat4 camera, glm::mat4 shipModelMatrix)
{
	glUseProgram(this->shader);
	glm::mat4 cameraProjectionMatrix;
	cameraProjectionMatrix = persp * camera;
	glUniformMatrix4fv(glGetUniformLocation(this->shader, "cameraProjectionMatrix"), 1, GL_FALSE, (float*)&cameraProjectionMatrix);
    glUniformMatrix4fv(glGetUniformLocation(this->shader, "shipModelMatrix"), 1, GL_FALSE, (float*)&shipModelMatrix);
    glUseProgram(0);
}

bool ParticleEffect::isActive()
{
    return this->active;
}

glm::vec3 ParticleEffect::getPosition()
{
    return this->position;
}

GLuint ParticleEffect::selectTexture(float age)
{   
    int index;
    if (age >= 1) {
        index = 63;
    }
    else {
        index = int(age / (this->delta * 10));
    }
    //std::cout << "index: " << index << std::endl;
    return this->textures[index];
}
