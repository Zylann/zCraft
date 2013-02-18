#version 150 core

in vec2 in_Position;
in vec4 in_Color;
in vec2 in_TexCoord0;

out vec4 color;
out vec2 texCoord0;

uniform mat4 modelview;

void main()
{
    gl_Position = modelview * vec4(in_Position, 0.0, 1.0);
    color = in_Color;
    texCoord0 = in_TexCoord0;
}
