#version 430 core

layout (location = 0) in vec4 vertex;

out vec2 TexCoords;

uniform mat4 cameraProjectionMatrix;
uniform vec3 particlePosition;
uniform mat4 shipModelMatrix;

void main()
{
	float scale = 500.0f;
    TexCoords = vertex.zw;
    gl_Position = cameraProjectionMatrix * vec4((vertex.xy) + particlePosition.xy, particlePosition.z, 1.0);
}
