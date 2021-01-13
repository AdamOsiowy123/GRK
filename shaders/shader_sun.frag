#version 430 core

uniform vec3 objectColor;
uniform vec3 cameraPos;

in vec3 interpNormal;

void main()
{
	vec3 normalized = normalize(interpNormal);
	vec3 viewDirection = normalize(cameraPos - normalized);
	float intensity = max(dot(normalized, viewDirection), 0.0);
	gl_FragColor = vec4(vec3(objectColor.x, objectColor.y * intensity * 2, objectColor.z), 1.0);
}
