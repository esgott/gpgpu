#version 130

uniform sampler2D inputMap;

out vec4 outColor;

const float deltat = 0.00001;
const float deltax = 0.01;
const float sqrc = 200.0;

const float sigma = 0.0006;

// TODO
//
// data := texelFetch(inputMap, ivec2(gl_FragCoord), 0)
// u := data.x
// u0 := data.x
// v := data.y
// v0 := data.y
// ud2 := Laplace filter U0 (| 0  1  0 |
//                           | 1 -4  1 |
//                           | 0  1  0 |
// a := sqrc * ud2 / deltax^2
// u := u0 + v * deltat + a / 2.0 * deltat^2
// v := (1.0 - sigma * deltat) * v0 + a * deltat
//
// ud2 := Laplace filter U (| 0  1  0 |
//                          | 1 -4  1 |
//                          | 0  1  0 |
// a := sqrc * ud2 / deltax^2;
// u := u0 +  v * deltat + a / 2.0 * deltat^2;
// v := (1.0 - sigma * deltat) * v0  + a * deltat;
// out := u,v

void main(void) {
    outColor = vec4(0.0);
}
