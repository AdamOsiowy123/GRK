#version 430 core

uniform vec3 objectColor;
uniform vec3 cameraPos;
uniform vec3 lightPos;


in vec3 interpNormal;
in vec3 vertexPos;

void main()
{
	vec3 lightDir = normalize(vertexPos - lightPos);
	vec3 normal = normalize(interpNormal);
	float diffuse = max(dot(-lightDir, normal), 0.0);
	vec3 viewDirection = normalize(cameraPos - vertexPos);
	vec3 R = reflect(lightDir, normal);
	float specular = pow(max(dot(R, viewDirection), 0.0), 250);
	gl_FragColor = vec4(objectColor * diffuse + vec3(1.0) * specular, 1.0);
}
