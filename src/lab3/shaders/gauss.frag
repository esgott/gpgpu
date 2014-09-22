#version 130

uniform sampler2D colorMap;

const float kernel[9] = float[9]( 1.0, 2.0, 1.0,
                                  2.0, 4.0, 2.0,
                                  1.0, 2.0, 1.0);
out vec4 outColor;

// TODO
// LOOP X = -1 .. 1
//  LOOP Y = -1 .. 1
//   texelValue[gl_FragCoord.x + X, gl_FragCoord.y + Y] * kernel[X+1,Y+1] / 16.0
//
// texelValue: texelFetch(samplerName, iCoord, mipmap)
//             texture2D(samplerName, nCoord)
// textureSize: textureSize(samplerName, mipmap)

void main() {
    outColor = vec4(0.0);
}
