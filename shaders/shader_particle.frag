#version 430 core

in vec3 TexCoords;

uniform sampler2D tex;

void main()
{
    vec2 modifiedTexCoord = vec2(TexCoords.x, 1.0 - TexCoords.y);
    if(texture2D(tex, TexCoords.xy).a != 1.0f){
    discard;
    }
    gl_FragColor  = texture2D(tex, TexCoords.xy);
}


