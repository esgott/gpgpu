#version 130

out vec4 outcolor;
in vec4 nodedata;

void main() {
    outcolor = nodedata;
}
