#version 130

out vec4 outcolor;
in vec2 fTexCoord;

// TODO
// fTexCoord -> outcolor
void main()
{
	outcolor = vec4(fTexCoord, 0, 0);
}
