#version 120

uniform float depth;
uniform float interval;
uniform vec4 sliceColor;

void main()
{
	float linearDepth = 1.f / gl_FragCoord.w;

	// Fog
	vec4 color = gl_Color;
//	vec4 fogColor = vec4(0.f, 0.f, 0.f, 1.f);
//	float fogK = linearDepth / 10.f;
//	color = color*(1.f-fogK) + fogColor*fogK;

	// Slice
	if(linearDepth > depth - interval && linearDepth < depth + interval)
	{
//		float k = abs((linearDepth - depth) / interval);
		float k = 1.f - (linearDepth - depth + interval) / (2.0 * interval);
		gl_FragColor = color*k + sliceColor * (1.f-k);
	}
	else
		gl_FragColor = color;
}
