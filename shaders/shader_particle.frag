#version 430 core

in vec2 TexCoords;

uniform sampler2D tex;

void main()
{
    vec2 modifiedTexCoord = vec2(TexCoords.x, 1.0 - TexCoords.y);
    gl_FragColor  = texture2D(tex, modifiedTexCoord.xy) * 2.0f;
}


