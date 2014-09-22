#version 130

const vec2 center = vec2(-1.68, -1.23);
const float zoom = 2.35;
const float iteration = 100.0;
const bool fractalType = true;
const vec2 k = vec2(0.353, 0.288);

in vec2 fTexCoord;

out vec4 outColor;

// TODO
// c = texcoord * zoom + center
// z = c
//
// Iteration
// Julia      := z^2 + c
// Mandelbrot := z^2 + k 
//
// IF divergent: outcolor := 0
// ELSE outcolor := 1

void main() {

}
