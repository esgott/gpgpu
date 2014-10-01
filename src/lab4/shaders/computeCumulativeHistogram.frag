#version 130

uniform sampler2D inputMap;
uniform float offset;

in vec2 fTexCoord;

out vec4 outColor;

// TODO
//
// outColor = texture(samplePos) + texture(samplePos + offset)
void main(void) {

}
