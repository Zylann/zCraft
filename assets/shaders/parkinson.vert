#version 120

uniform float time;

float rand(vec2 seed) // Because I couldn't get noise to work
{
	return fract(sin(dot(seed, vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	gl_FrontColor = gl_Color;
	vec4 pos = gl_Vertex;
	const float k = 0.1;
	pos.x += k * rand(vec2(pos.x+time, pos.y)); // Note : time +/- were chosen at random
	pos.y += k * rand(vec2(pos.x, pos.y+time));
	pos.z += k * rand(vec2(pos.x-time, pos.y));
    gl_Position = gl_ModelViewProjectionMatrix * pos;

}
