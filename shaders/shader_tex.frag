#version 430 core

uniform sampler2D textureSampler;
uniform vec3 cameraPos;
uniform vec3 lightPos;

in vec3 interpNormal;
in vec2 interpTexCoord;
in vec3 vertexPos;

void main()
{
	vec2 modifiedTexCoord = vec2(interpTexCoord.x, 1.0 - interpTexCoord.y); // Poprawka dla tekstur Ziemi, ktore bez tego wyswietlaja sie 'do gory nogami'
	vec3 lightDir = normalize(vertexPos - lightPos);
	vec3 color = texture2D(textureSampler, modifiedTexCoord).rgb;
	vec3 L = -lightDir;
	vec3 V = normalize(cameraPos - vertexPos);
	vec3 N = normalize(interpNormal);
	vec3 R = reflect(-normalize(L), N);

	float diffuse = max(dot(L, N), 0.0);
	
	float specular_pow = 100;
	
	float specular = 0.0;
	if(diffuse > 0.0){

		specular = pow(max(0, dot(R, V)), specular_pow);
	}

	vec3 lightColor = vec3(1);
	vec3 shadedColor = color * diffuse + lightColor * specular;
	
	float ambient = 0.2;

	gl_FragColor = vec4(mix(color, shadedColor, 1.0 - ambient), 1.0);
}
