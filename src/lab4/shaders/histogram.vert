#version 130

uniform sampler2D inputBuffer;

in vec4 position;

out vec4 color;

float I(vec2 coord) {
    vec4 color = texture(inputBuffer, coord);
    return(dot(color.rgb, vec3(0.21, 0.39, 0.4)));
}

// TODO
//
// luminance := I(vertex position)
// gl_Position := histogram[bucket]
// color := 1
void main(void) {
    float luminance = I(position.xy);
    gl_Position = vec4(2 * (luminance - 0.5), 0, 0, 1);
    color = vec4(1);
}
