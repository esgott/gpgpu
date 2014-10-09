#version 130

in vec4 position;

out vec4 fcolor;

void main(void) {
    fcolor = vec4(1,1,0,position.z);
    gl_Position = vec4(position.xy,0,1);
}
