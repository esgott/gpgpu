#version 130

uniform sampler2D inputMap;

out vec4 outColor;

const float deltat = 0.001;
const float deltax = 0.01;
const float sqrc = 200.0;

// TODO
//
// data := texelFetch(inputMap, ivec2(gl_FragCoord), 0)
// u := data.x
// v := data.y
// ud2 := Laplace filter (| 0  1  0 |
//                        | 1 -4  1 |
//                        | 0  1  0 |
// u := u + v * deltat
// v := v + sqrc * ud2 * deltat
//
// out := u,v

void main(void) {
    outColor = vec4(0.0);
}
