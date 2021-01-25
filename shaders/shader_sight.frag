#version 430 core

uniform vec3 objectColor;

void main()
{
	gl_FragColor = glm::vec4(objectColor,1.0f);
}
