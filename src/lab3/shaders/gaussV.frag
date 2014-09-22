#version 130

uniform sampler2D colorMap;
const float kernel[3] = float[3](1.0, 2.0, 1.0);
out vec4 outColor;

// TODO
// LOOP Y = -1 .. 1
//  texelValue[gl_FragCoord.x, gl_FragCoord.y + Y] * kernel[Y+1] / 4.0
//
// texelValue: texelFetch(samplerName, iCoord, mipmap)
//             texture2D(samplerName, nCoord)
// textureSize: textureSize(samplerName, mipmap)

void main() {
    outColor = vec4(0.0);
}
