#version 130

uniform vec2 center;
uniform float zoom;
uniform float iteration = 100.0;
uniform bool fractalType;
uniform vec2 k = vec2(0.353, 0.288);

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
    vec2 c = fTexCoord * zoom + center;
    vec2 z = c;
    int i = 0;
    
    for (i = 0; i < iteration; i++) {
        if (fractalType) {
            z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
        } else {
            z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + k;
        }
        if (dot(z, z) > 4) {
            break;
        }
    }
    
    outColor = vec4(vec3(1.0 - float(i) / iteration), 1.0);
}

