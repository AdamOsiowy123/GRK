#include "ParticleEffect.h"

ParticleEffect::ParticleEffect(GLuint shader, unsigned int amount, float delta, std::vector<GLuint> textures,glm::vec3 position)
{
	this->shader = shader;
	this->amount = amount;
	this->delta = delta;
	this->active = true;
	this->textures = textures;
    this->position = position;
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

    for (unsigned int i = 0; i < this->amount; ++i)
        this->particles.push_back(Particle(this->position));

    srand(time(NULL));
}

void ParticleEffect::draw()
{
    glUseProgram(this->shader);

    for (Particle p : this->particles)
    {
        if (p.Life > 0.0f)
        {
            glUniform3f(glGetUniformLocation(this->shader, "position"), p.Position.x, p.Position.y,p.Position.z);
            glBindTexture(GL_TEXTURE_2D, selectTexture(p.Age));
            glBindVertexArray(this->VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    glUseProgram(0);
}

void ParticleEffect::update()
{
    for (unsigned int i = 0; i < this->particles.size(); ++i)
    {
        Particle& p = this->particles[i];
        p.Life -= this->delta; 
        p.Age += (0.015625f * (rand()%3 + 1));
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
	std::sort(&particles[0], &particles[amount-1]);
}

void ParticleEffect::deleteDeadParticles()
{
    std::vector<Particle> copy;
    for (auto p : this->particles) {
        if (p.Life > 0 && p.Age < 1.0f) {
            copy.push_back(p);
        }
    }
    this->particles = copy;
}

void ParticleEffect::sendProjectionToShader(glm::mat4 persp, glm::mat4 camera)
{
	glUseProgram(this->shader);
	glm::mat4 trans;
	trans = persp * camera;
	glUniformMatrix4fv(glGetUniformLocation(this->shader, "projection"), 1, GL_FALSE, (float*)&trans);
	glUseProgram(0);
}

GLuint ParticleEffect::selectTexture(float age)
{   
    int index;
    if (age > 1) {
        index = 63;
    }
    else {
        index = int(age / 0.015625f) - 1;
    }
    return this->textures[index];
}
