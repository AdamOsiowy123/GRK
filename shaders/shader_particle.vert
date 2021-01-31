#version 430 core

layout (location = 0) in vec4 vertex;

out vec3 TexCoords;

uniform mat4 projection;
uniform vec3 position;

void main()
{
	float scale = 0.9f;
    TexCoords = vertex.xyz;
    gl_Position = projection * vec4((vertex.xyz * scale) + position, 1.0);
}
