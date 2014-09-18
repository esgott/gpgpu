#version 130

uniform sampler2D textureMap;
uniform float threshold;

in vec2 fTexCoord;
out vec4 outColor;

float I (vec2 coord){
    vec4 color = texture(textureMap, coord);
    return(dot(color.rgb, vec3(0.21, 0.39, 0.4)));
}

// TODO
// IF I(ftexcoord) > threshold: outcolor = 1
// ELSE outcolor := 0
void main()
{
    if (I(fTexCoord) > threshold) {
        outColor = vec4(0);
    } else {
        outColor = vec4(1);
    }
}
