#version 130

uniform sampler2D inputMap;

uniform bool pass;

out vec4 outColor;

const float deltat = 0.001;
const float deltax = 0.01;
const float sqrc = 20000.0;

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
    vec4 data = texelFetch(inputMap, ivec2(gl_FragCoord), 0);
    float u = data.x;
    float v = data.y;

    float ud2 = texelFetch(inputMap, ivec2(gl_FragCoord) + ivec2(-1,  0),0).x +
                texelFetch(inputMap, ivec2(gl_FragCoord) + ivec2( 1,  0),0).x +
                texelFetch(inputMap, ivec2(gl_FragCoord) + ivec2( 0, -1),0).x +
                texelFetch(inputMap, ivec2(gl_FragCoord) + ivec2( 0,  1),0).x -
                4 * u;

    if (pass) {
        float um = u + v * deltat / 2.0;
        float vm = u + sqrc * ud2 * deltat / 2.0;
        outColor = vec4(u, v, um, vm);
    } else {
        float um = data.z;
        float vm = data.w;
        u = u + vm * deltat;
        v = u + sqrc * ud2 * deltat;
        outColor = vec4(u, v, 0, 0);
    }

    u = u + v * deltat;
    v = v + sqrc * ud2 * deltat;

    outColor = vec4(0.0);
}
