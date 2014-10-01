#version 130

uniform sampler2D inputBuffer;
uniform int levels;

in vec2 fTexCoord;

out vec4 outColor;

float I (vec2 coord) {
    vec4 color = texture(inputBuffer, coord);
    return(dot(color.rgb, vec3(0.21, 0.39, 0.4)));
}

// TODO
//
// data := I(sample_position)
// bin  := nearest_histogram_bin(data)
// outColor := bin
void main() {

}
