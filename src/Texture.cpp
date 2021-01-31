#include "Texture.h"

#include <fstream>
#include <iterator>
#include <vector>
#include "picopng.h"

typedef unsigned char byte;

GLuint Core::LoadTexture( const char * filepath )
{
	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	std::ifstream input( filepath, std::ios::binary );
	std::vector<char> buffer((
		std::istreambuf_iterator<char>(input)), 
		(std::istreambuf_iterator<char>()));

	unsigned long w, h;
	std::vector<unsigned char> decoded;
	decodePNG(decoded, w, h, (unsigned char*)&buffer[0], buffer.size(), true);
	

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &decoded[0]);
	glGenerateMipmap(GL_TEXTURE_2D);

	return id;
}

void Core::SetActiveTexture(GLuint textureID, const char * shaderVariableName, GLuint programID, int textureUnit)
{
	glUniform1i(glGetUniformLocation(programID, shaderVariableName), textureUnit);
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

std::vector<GLuint> Core::LoadParticleTextures()
{
	std::vector<GLuint> v;
	v.emplace_back(Core::LoadTexture("textures/particles/p0.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p1.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p2.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p3.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p4.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p5.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p6.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p7.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p8.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p9.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p10.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p11.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p12.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p13.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p14.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p15.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p16.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p17.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p18.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p19.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p20.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p21.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p22.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p23.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p24.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p25.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p26.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p27.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p28.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p29.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p30.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p31.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p32.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p33.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p34.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p35.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p36.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p37.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p38.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p39.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p40.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p41.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p42.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p43.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p44.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p45.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p46.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p47.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p48.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p49.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p50.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p51.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p52.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p53.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p54.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p55.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p56.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p57.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p58.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p59.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p60.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p61.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p62.png"));
	v.emplace_back(Core::LoadTexture("textures/particles/p63.png"));
	return v;
}