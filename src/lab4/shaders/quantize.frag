#version 130

uniform sampler2D inputBuffer;
uniform int levels;

in vec2 fTexCoord;

out vec4 outColor;

float I(vec2 coord) {
    vec4 color = texture(inputBuffer, coord);
    return(dot(color.rgb, vec3(0.21, 0.39, 0.4)));
}

float nearest_histogram_bin(float data) {
    float step = 1.0 / levels;

    for (int i = 0; i < levels; i++) {
        if (data < (i * step)) {
            return i * step;
        }
    }

    return 1.0;
}

// TODO
//
// data := I(sample_position)
// bin  := nearest_histogram_bin(data)
// outColor := bin
void main() {
    float data = I(vec2(fTexCoord.x, -fTexCoord.y));
    float bin = nearest_histogram_bin(data);
    outColor = vec4(bin);
}
