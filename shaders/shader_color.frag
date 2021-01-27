#version 430 core

uniform vec3 objectColor;
uniform vec3 cameraPos;
uniform vec3 lightPos;
uniform vec3 lightPos2;


in vec3 interpNormal;
in vec3 vertexPos;
in vec3 vertexPos2;

void main()
{

	float cosX = cos(3.14 + vertexPos2.x * 3.14 /80);
	vec3 objColor;
	if(cosX > 0.7 && cosX <= 0.85f){
		objColor = vec3(1.0f, 1.0f, 1.0f) * 1.2f;
	}
	else if(cosX > 0.85f){
		objColor = vec3(1.0f, 1.0f, 0.0f) * 1.2f;
	}
	else if(cosX <= 0.7f && cosX > 0.6f){
		objColor = vec3(0.0f, 1.0f, 0.0f);
	}
	else{
		objColor = vec3(0.368f * (cosX/1.5f + 1.5f), (cosX/1.5f + 1.5f) * 0.631f, (cosX/1.5f + 1.5f));
	}

	vec3 lightDir = normalize(vertexPos - lightPos);
	vec3 lightDir2 = normalize(vertexPos - lightPos2);
	vec3 normal = normalize(interpNormal);
	float diffuse = max(dot(-lightDir, normal), 0.0);
	float diffuse2 = max(dot(-lightDir2, normal), 0.0);
	vec3 viewDirection = normalize(cameraPos - vertexPos);
	vec3 R = reflect(lightDir, normal);
	vec3 R2 = reflect(lightDir2, normal);
	float specular = pow(max(dot(R, viewDirection), 0.0), 250);
	float specular2 = pow(max(dot(R2, viewDirection), 0.0), 250);
	float distance = length(vertexPos - lightPos);
	float distance2 = length(vertexPos - lightPos2);
	float attenuation = clamp( 500.0 / distance, 0.0, 1.0);
	float attenuation2 = clamp( 500.0 / distance2, 0.0, 1.0);
	vec3 lightColor = vec3(1.0);
	vec3 shadedColor = (objColor * diffuse + lightColor * specular) * attenuation + (objColor * diffuse2 + lightColor * specular2) * attenuation2;
	float ambient = 0.2;

	gl_FragColor = vec4(mix(objColor, shadedColor - ambient, 1.0 - 0.5* ambient), 1.0);
}
