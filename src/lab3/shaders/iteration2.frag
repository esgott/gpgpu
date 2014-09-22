#version 130

uniform sampler2D inputMap;

uniform bool pass;

out vec4 outColor;

const float deltat = 0.001;
const float deltax = 0.01;
const float sqrc = 200.0;

// TODO
//
// data := texelFetch(inputMap, ivec2(gl_FragCoord), 0)
// IF pass == 0
//     u := data.x
//     v := data.y
//     ud2 := Laplace filter U (| 0  1  0 |
//                              | 1 -4  1 |
//                              | 0  1  0 |
//     um := u + v * deltat / 2.0
//     vm := u + sqrc * ud2 * deltat / 2.0
//     out := u,v,um,vm
// ELSE
//     u := data.x
//     v := data.y
//     um := data.z
//     vm := data.w
//     ud2 := Laplace filter UM (| 0  1  0 |
//                               | 1 -4  1 |
//                               | 0  1  0 |
//     u := u + vm * deltat;
//     v := u + sqrc * ud2 * deltat
//     out := u,v

void main(void) {
    outColor = vec4(0.0);
}
