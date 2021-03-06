#version 130

uniform sampler2D textureMap;
uniform vec2 textureSize;

in vec2 fTexCoord;
out vec4 outColor;

float I (vec2 coord){
    vec4 color = texture(textureMap, coord);
    return(dot(color.rgb, vec3(0.21, 0.39, 0.4)));
}

// Prewitt
const float kernelX[9] = float[9](-1.0/6.0, 0.0, 1.0/6.0,
                                  -1.0/6.0, 0.0, 1.0/6.0,
                                  -1.0/6.0, 0.0, 1.0/6.0);

const float kernelY[9] = float[9](1.0/6.0,  1.0/6.0,  1.0/6.0,
                                      0.0,      0.0,      0.0,
                                 -1.0/6.0, -1.0/6.0, -1.0/6.0);

// Sobel
//const float kernelX[9] = float[9](-1.0/8.0, 0.0, 1.0/8.0,
//                                  -2.0/8.0, 0.0, 2.0/8.0,
//                                  -1.0/8.0, 0.0, 1.0/8.0);

//const float kernelY[9] = float[9](1.0/8.0,  2.0/8.0,  1.0/8.0,
//                                      0.0,      0.0,      0.0,
//                                 -1.0/8.0, -2.0/8.0, -1.0/8.0);


// TODO
// Gradient := LOOP i = 1..9 : I(texcoord + offset[i]) * kernel[i]
// outcolor := sqrt(Gradient) * 8.0
void main() {

    float step_w = 1.0/textureSize.x;
    float step_h = 1.0/textureSize.y;
    vec2 offset[9] = vec2[9](vec2(-step_w, -step_h), vec2(0.0, -step_h), vec2(step_w, -step_h),
                                 vec2(-step_w, 0.0),     vec2(0.0, 0.0),     vec2(step_w, 0.0),
                              vec2(-step_w, step_h),  vec2(0.0, step_h),  vec2(step_w, step_h));

    outColor = vec4(0.0);
}
