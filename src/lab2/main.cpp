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

int example = 3;

Shader* shaderMandelbrot;
bool fractalType;
float centerX;
float centerY;
float zoom;
float iteration;
float kReal;
float kIm;

void mandelbrot() {
    shaderMandelbrot->enable();
    shaderMandelbrot->bindUniformBool("fractalType", fractalType);
    shaderMandelbrot->bindUniformFloat("zoom", zoom);
    shaderMandelbrot->bindUniformFloat2("center", centerX, centerY);
    shaderMandelbrot->bindUniformFloat("iteration", iteration);
    shaderMandelbrot->bindUniformFloat2("k", kReal, kIm);
    fullscreenQuad->render(shaderMandelbrot);
    shaderMandelbrot->disable();
}

Shader* shaderThreshold;
float thresholdValue;

void threshold() {
    shaderThreshold->enable();
    shaderThreshold->bindUniformTexture("textureMap", texture->getTextureHandle(), 0);
    shaderThreshold->bindUniformFloat("threshold", thresholdValue);
    fullscreenQuad->render(shaderThreshold);
    shaderThreshold->disable();
}

Shader* shaderEdgeDetection;

void edgeDetection() {
    shaderEdgeDetection->enable();
    shaderEdgeDetection->bindUniformTexture("textureMap", texture->getTextureHandle(), 0);
    shaderEdgeDetection->bindUniformFloat2("textureSize", texture->getWidth(), texture->getHeight());
    fullscreenQuad->render(shaderEdgeDetection);
    shaderEdgeDetection->disable();
}

Shader* shaderConvolution;

void convolution() {
    shaderConvolution->enable();
    shaderConvolution->bindUniformTexture("textureMap", texture->getTextureHandle(), 0);
    shaderConvolution->bindUniformFloat2("textureSize", texture->getWidth(), texture->getHeight());
    fullscreenQuad->render(shaderConvolution);
    shaderConvolution->disable();
}

void reset() {
    fractalType = true;
    centerX = -1.68f;
    centerY = -1.23f;
    zoom = 2.35f;
    iteration = 100.0f;
    kReal = 0.353f;
    kIm = 0.288f;
    thresholdValue = 0.5f;
}

void init() {
    reset();
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
    case 'q':
        exit(0);
        break;
    case 'R':
        reset();
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
    case 'k':
        fractalType = !fractalType;
        break;
    case '+':
        zoom *= 0.9;
        thresholdValue *= 0.9;
        break;
    case '-':
        zoom *= 1.1;
        thresholdValue *= 1.1;
        break;
    case 'w':
        centerY -= 00.1;
        break;
    case 's':
        centerY += 00.1;
        break;
    case 'a':
        centerX -= 00.1;
        break;
    case 'd':
        centerX += 00.1;
        break;
    case 'r':
        kReal *= 1.01;
        break;
    case 'f':
        kReal *= 0.99;
        break;
    case 't':
        kIm *= 1.01;
        break;
    case 'g':
        kIm *= 0.99;
        break;
    case '[':
        iteration += 10;
        break;
    case ']':
        iteration -= 10;
        break;
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

void idle() {
    static bool startup = true;
    if (startup) {
        glutPostRedisplay();
        startup = false;
    }
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
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}

