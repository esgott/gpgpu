#version 130

uniform sampler2D textureMap;
uniform vec2 textureSize;

in vec2 fTexCoord;
out vec4 outColor;

const float kernel[9] = float[9](1.0, 2.0, 1.0,
                                 2.0, 4.0, 2.0,
                                 1.0, 2.0, 1.0);

// TODO
// outcolor := LOOP i = 1..9 : texture2D(textureMap, texcoord + offset[i]) * kernel[i] / 16.0
void main() {

    float step_w = 1.0/textureSize.x;
    float step_h = 1.0/textureSize.y;
    vec2 offset[9] = vec2[9](vec2(-step_w, -step_h), vec2(0.0, -step_h), vec2(step_w, -step_h),
                             vec2(-step_w, 0.0),     vec2(0.0, 0.0),         vec2(step_w, 0.0),
                             vec2(-step_w, step_h),  vec2(0.0, step_h),   vec2(step_w, step_h));

    outColor = vec4(0.0);
}
