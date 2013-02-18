#version 150 core

in vec3 in_Position;
in vec4 in_Color;
in vec2 in_TexCoord0;
in vec3 in_Normal;

out vec4 color;
out vec2 texCoord0;

uniform mat4 projection;
uniform mat4 modelview;

void main()
{
    gl_Position = projection * modelview * vec4(in_Position, 1.0);
    color = in_Color;
    texCoord0 = in_TexCoord0;
}
