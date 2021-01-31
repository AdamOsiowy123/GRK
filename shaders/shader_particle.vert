#version 430 core

layout (location = 0) in vec4 vertex;

out vec3 TexCoords;

uniform mat4 projection;
uniform vec3 position;
uniform mat4 shipProjectionMatrix;

void main()
{
	float scale = 500.0f;
    TexCoords = vertex.xyz;
    gl_Position = projection * shipProjectionMatrix * vec4((vertex.xyz * scale) + position, 1.0);
}
