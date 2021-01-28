#version 430 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoord;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in vec3 vertexTangent;
layout(location = 4) in vec3 vertexBitangent;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelMatrix;
uniform vec3 lightPos;
uniform vec3 lightPos2;
uniform vec3 cameraPos;

out vec3 interpNormal;
out vec2 interpTexCoord;
out vec3 vertexPos;
out vec3 lightDirTS;
out vec3 lightDirTS2;
out vec3 viewDirTS;
out vec3 lightPosOut;
out vec3 lightPosOut2;

void main()
{
	gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);
	vec3 vertPos = (modelMatrix * vec4(vertexPosition, 1.0)).xyz;
	interpNormal = (modelMatrix * vec4(vertexNormal, 0.0)).xyz;
	vec3 normal = (modelMatrix * vec4(vertexNormal, 0.0)).xyz;
	vec3 tangent = (modelMatrix * vec4(vertexTangent, 0.0)).xyz;
	vec3 bitangent = (modelMatrix * vec4(vertexBitangent, 0.0)).xyz;
	mat3 TBN = transpose(mat3(tangent, bitangent, normal));
	interpTexCoord = vertexTexCoord;
	vertexPos = vec3(modelMatrix * vec4(vertexPosition, 1.0));
	vec3 viewDir = normalize(cameraPos - vertPos);
	vec3 lightDir = normalize(vertexPos - lightPos);
	vec3 lightDir2 = normalize(vertexPos - lightPos2);
	lightDirTS = TBN * lightDir;
	lightDirTS2 = TBN * lightDir2;
	viewDirTS = TBN * viewDir;
	vec3 lightPosOut = lightPos;
	vec3 lightPosOut2 = lightPos2;
}
