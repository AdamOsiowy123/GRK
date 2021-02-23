#version 430 core

layout (location = 0) in vec4 vertex;

out vec3 TexCoords;

uniform mat4 cameraProjectionMatrix;
uniform vec3 particlePosition;
uniform mat4 shipModelMatrix;

void main()
{
	float scale = 500.0f;
    TexCoords = vertex.xyz;
    gl_Position = cameraProjectionMatrix * shipModelMatrix * vec4((vertex.xyz * scale) + particlePosition, 1.0);
}
