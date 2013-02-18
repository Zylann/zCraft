#version 150 core

in vec4 color;
in vec2 texCoord0;

out vec4 out_Color;

uniform sampler2D texture0;

void main()
{
    out_Color = texture(texture0, texCoord0) * color;
}
