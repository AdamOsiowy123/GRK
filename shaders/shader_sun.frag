#version 430 core

uniform sampler2D textureSampler;
uniform vec3 objectColor;
uniform vec3 cameraPos;

in vec3 interpNormal;
in vec2 interpTexCoord;
in vec3 vertexPos;

void main()
{
	vec2 modifiedTexCoord = vec2(0.7 - interpTexCoord.x, interpTexCoord.y);
	vec3 normalized = normalize(interpNormal);
	vec3 viewDirection = normalize(cameraPos - vertexPos);
	float intensity = max(dot(normalized, viewDirection), 0.0);
	vec3 color = texture2D(textureSampler, modifiedTexCoord).rgb;
	//gl_FragColor = vec4(vec3(objectColor.x, objectColor.y * intensity * 2, objectColor.z), 1.0);
	gl_FragColor = vec4(mix(color, color, 1.0), 1.0);
}
