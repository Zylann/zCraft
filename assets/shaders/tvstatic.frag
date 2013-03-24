#version 120

uniform float time;

float rand(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	float r = rand(vec2(gl_FragCoord.x, gl_FragCoord.y + time));
    //gl_FragColor = vec4(r, r, r, 1.0);
    gl_FragColor = vec4(gl_Color.r*r, gl_Color.g*r, gl_Color.b*r, 1.0);
}
