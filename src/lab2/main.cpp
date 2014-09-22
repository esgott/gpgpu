/*
 *
 * Copyright © 2010-2011 Balázs Tóth <tbalazs@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

#include "framebuffer.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "quad.hpp"

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

int windowWidth = 600;
int windowHeight = 600;

Quad* fullscreenQuad;
Texture2D* texture;
Shader* simpleShader;

int example = 1;

// Mandelbrot set
Shader* shaderMandelbrot;
bool fractalType = true;
float centerX = -1.68f;
float centerY = -1.23f;
float zoom = 2.35f;
float iteration = 100.0f;
float kReal = 0.353f;
float kIm = 0.288f;

// TODO
// Mandelbrot set
void mandelbrot() {

}

// Threshold
Shader* shaderThreshold;
float thresholdValue = 0.5f;

// TODO
// Thresholding
void threshold() {

}

// Edge detection
Shader* shaderEdgeDetection;

// TODO
// Edge detection
void edgeDetection() {

}

// Convolution
Shader* shaderConvolution;

// TODO
// Convolution
void convolution() {

}

void init() {
    glewInit();

    fullscreenQuad = new Quad();
    simpleShader = new Shader("../src/lab2/shaders/passthrough.vert", "../src/lab2/shaders/simple.frag");

    shaderMandelbrot = new Shader("../src/lab2/shaders/passthrough.vert", "../src/lab2/shaders/mandelbrot.frag");

    texture = new Texture2D();
    texture->loadFromFile(std::string("../img/lena.jpg"));

    shaderThreshold = new Shader("../src/lab2/shaders/passthrough.vert", "../src/lab2/shaders/threshold.frag");
    shaderEdgeDetection = new Shader("../src/lab2/shaders/passthrough.vert", "../src/lab2/shaders/edgeDetection.frag");
    shaderConvolution = new Shader("../src/lab2/shaders/passthrough.vert", "../src/lab2/shaders/convolution.frag");

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void display() {
    glClearColor(0.17f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch (example) {
    case 1:
        glutReshapeWindow(600, 600);
        mandelbrot();
        break;

    case 2:
        glutReshapeWindow(texture->getWidth(), texture->getHeight());
        threshold();
        break;

    case 3:
        glutReshapeWindow(texture->getWidth(), texture->getHeight());
        edgeDetection();
        break;

    case 4:
        glutReshapeWindow(texture->getWidth(), texture->getHeight());
        convolution();
        break;
    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {

    case 27:
        exit(0);
        break;

    case '1':
        example = 1;
        break;
    case '2':
        example = 2;
        break;
    case '3':
        example = 3;
        break;
    case '4':
        example = 4;
        break;

        // TODO
        // additional key bindings

    default:
        std::cout << "Unbinded key: " << (unsigned int) key << std::endl;
    }

    glutPostRedisplay();
}

void reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("GPGPU 2. labor: glsl");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return (0);
}

