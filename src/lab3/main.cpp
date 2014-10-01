/*
 *
 * Copyright © 2010-2013 Balázs Tóth <tbalazs@gmail.com>
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
#include <GL/glu.h>

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

Shader* gaussShader;
// Single pass Gauss filter
void gaussSingle() {
    gaussShader->enable();
    gaussShader->bindUniformTexture("colorMap", texture->getTextureHandle(), 0);
    fullscreenQuad->render(gaussShader);
    gaussShader->disable();
}

Framebuffer* computeBuffer[2];
int inputBuffer = 0;
int npasses = 15;

void gaussMultipass() { // TODO
    // LOOP I = 0 .. npasses
    //  IF I == npasses - 1
    //   renderTarget := screen
    //  ELSE
    //   renderTarget := computeBuffer[(inputBuffer + 1) % 2]
    //
    //  IF npasses == 0
    //   colorMap := texture
    //  ELSE
    //   colorMap := computeBuffer[inputBuffer]->getColorBuffer(0)
    //
    //  GaussShader
    //  inputBuffer = (inputBuffer + 1) % 2
    gaussShader->enable();

    computeBuffer[(inputBuffer) % 2]->setRenderTarget();
    gaussShader->bindUniformTexture("colorMap", texture->getTextureHandle(), 0);
    fullscreenQuad->render(gaussShader);

    for (int i = 1; i < npasses - 1; i++) {
        computeBuffer[(inputBuffer + 1) % 2]->setRenderTarget();
        gaussShader->bindUniformTexture("colorMap", computeBuffer[inputBuffer % 2]->getColorBuffer(0), 0);
        fullscreenQuad->render(gaussShader);
        inputBuffer++;
    }

    computeBuffer[(inputBuffer) % 2]->disableRenderTarget();
    gaussShader->bindUniformTexture("colorMap", computeBuffer[(inputBuffer + 1) % 2]->getColorBuffer(0), 0);
    fullscreenQuad->render(gaussShader);

    gaussShader->disable();
}

Shader* gaussShaderV;
Shader* gaussShaderH;
// TODO
// LOOP I = 0 .. npasses
//  IF I == npasses - 1
//   renderTarget := screen
//  ELSE
//   renderTarget := computeBuffer[(inputBuffer + 1) % 2]
//
//  IF npasses == 0
//   colorMap := texture
//  ELSE
//   colorMap := computeBuffer[inputBuffer]->getColorBuffer(0)
//
//  GaussShaderH
//  inputBuffer = (inputBuffer + 1) % 2
//  GaussShaderV
//  inputBuffer = (inputBuffer + 1) % 2
void gaussSeparableMultipass() {

}

Shader* WE_addForce;
Shader* WE_iteration_1;
Shader* WE_iteration_2;
Shader* WE_iteration_3;
Shader* WE_visualize;

Framebuffer* WE_computeBuffer[2];
//TODO
//
// Euler integration
//
// renderTarget := WE_computeBuffer[(inputBuffer + 1) % 2]
// inputMap := WE_computeBuffer[inputBuffer]->getColorBuffer(0) , textureUnit := 0
// WE_iteration_1
// inputBuffer := (inputBuffer + 1) % 2;
//
// renderTarget := screen
// inputMap := WE_computeBuffer[inputBuffer]->getColorBuffer(0), textureUnit := 0
// WE_visualize
void waveEquation1() {
    WE_iteration_1->enable();

    WE_computeBuffer[(inputBuffer + 1) % 2]->setRenderTarget();
    WE_iteration_1->bindUniformTexture("inputMap", WE_computeBuffer[inputBuffer % 2]->getColorBuffer(0), 0);
    fullscreenQuad->render(WE_iteration_1);

    inputBuffer++;

    WE_iteration_1->disable();

    WE_visualize->enable();

    WE_computeBuffer[inputBuffer % 2]->disableRenderTarget();
    WE_visualize->bindUniformTexture("inputMap", WE_computeBuffer[inputBuffer % 2]->getColorBuffer(0), 0);
    fullscreenQuad->render(WE_visualize);

    WE_visualize->disable();
}

//TODO
//
// 2nd order Runge-Kutta integration
//
// renderTarget := WE_computeBuffer[(inputBuffer + 1) % 2]
// pass := 0
// inputMap := WE_computeBuffer[inputBuffer]->getColorBuffer(0) , textureUnit := 0
// WE_iteration_2
// inputBuffer := (inputBuffer + 1) % 2;
//
// renderTarget := WE_computeBuffer[(inputBuffer + 1) % 2]
// pass := 1
// inputMap := WE_computeBuffer[inputBuffer]->getColorBuffer(0) , textureUnit := 0
// WE_iteration_2
// inputBuffer := (inputBuffer + 1) % 2;
//
// renderTarget := screen
// inputMap := WE_computeBuffer[inputBuffer]->getColorBuffer(0), textureUnit := 0
// WE_visualize
void waveEquation2() {
    WE_iteration_2->enable();

    WE_computeBuffer[(inputBuffer + 1) % 2]->setRenderTarget();
    WE_iteration_2->bindUniformTexture("inputMap", WE_computeBuffer[inputBuffer % 2]->getColorBuffer(0), 0);
    WE_iteration_2->bindUniformBool("pass", false);
    fullscreenQuad->render(WE_iteration_2);

    WE_computeBuffer[inputBuffer % 2]->setRenderTarget();
    WE_iteration_2->bindUniformTexture("inputMap", WE_computeBuffer[(inputBuffer + 1) % 2]->getColorBuffer(0), 0);
    WE_iteration_2->bindUniformBool("pass", true);
    fullscreenQuad->render(WE_iteration_2);

    WE_iteration_2->disable();

    WE_visualize->enable();

    WE_computeBuffer[(inputBuffer + 1) % 2]->disableRenderTarget();
    WE_visualize->bindUniformTexture("inputMap", WE_computeBuffer[inputBuffer % 2]->getColorBuffer(0), 0);
    fullscreenQuad->render(WE_visualize);

    WE_visualize->disable();
}

//TODO
//
// Verlet integration
//
// renderTarget := WE_computeBuffer[(inputBuffer + 1) % 2]
// inputMap := WE_computeBuffer[inputBuffer]->getColorBuffer(0) , textureUnit := 0
// WE_iteration_1
// inputBuffer := (inputBuffer + 1) % 2;
//
// renderTarget := screen
// inputMap := WE_computeBuffer[inputBuffer]->getColorBuffer(0), textureUnit := 0
// WE_visualize
void waveEquation3() {

}

void resetWave() {
    WE_computeBuffer[0]->clear();
    WE_computeBuffer[1]->clear();
}

void addForce(int x, int y) {
    WE_computeBuffer[inputBuffer % 2]->setRenderTarget();
    WE_addForce->enable();
    WE_addForce->bindUniformInt2("center", x, 600 - y);
    fullscreenQuad->render(WE_addForce);
    WE_addForce->disable();
    WE_computeBuffer[inputBuffer % 2]->disableRenderTarget();
}

int example = 1;

void init() {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    } else {
        if (GLEW_VERSION_3_3) {
            std::cout << "Driver supports OpenGL 3.3\nDetails:" << std::endl;
            std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
            std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
            std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
            std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
            std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
        }
    }

    // FIXME: GLEW Init causes "Invalid enumerant" OpenGL error!
    //        Supressing it now as the pipeline seems working.
    GLenum error = glGetError();
    if (GL_NO_ERROR != error) {
        // std::cout << "Error: " << gluErrorString(error) << std::endl;
    }

    fullscreenQuad = new Quad();
    simpleShader = new Shader("../src/lab3/shaders/passthrough.vert", "../src/lab3/shaders/simple.frag");
    gaussShader = new Shader("../src/lab3/shaders/passthrough.vert", "../src/lab3/shaders/gauss.frag");
    gaussShaderH = new Shader("../src/lab3/shaders/passthrough.vert", "../src/lab3/shaders/gaussH.frag");
    gaussShaderV = new Shader("../src/lab3/shaders/passthrough.vert", "../src/lab3/shaders/gaussV.frag");
    WE_addForce = new Shader("../src/lab3/shaders/passthrough.vert", "../src/lab3/shaders/addForce.frag");
    WE_iteration_1 = new Shader("../src/lab3/shaders/passthrough.vert", "../src/lab3/shaders/iteration.frag");
    WE_iteration_2 = new Shader("../src/lab3/shaders/passthrough.vert", "../src/lab3/shaders/iteration2.frag");
    WE_iteration_3 = new Shader("../src/lab3/shaders/passthrough.vert", "../src/lab3/shaders/iteration3.frag");
    WE_visualize = new Shader("../src/lab3/shaders/passthrough.vert", "../src/lab3/shaders/visualize.frag");

    texture = new Texture2D();
    texture->loadFromFile(std::string("../img/lena.jpg"));

    if (1 == example) {
        glutReshapeWindow(texture->getWidth(), texture->getHeight());
    }

    computeBuffer[0] = new Framebuffer(texture->getWidth(), texture->getHeight(), 1);
    computeBuffer[1] = new Framebuffer(texture->getWidth(), texture->getHeight(), 1);

    WE_computeBuffer[0] = new Framebuffer(600, 600, 1);
    WE_computeBuffer[1] = new Framebuffer(600, 600, 1);

    resetWave();
    addForce(300, 300);
}

void display() {
    glClearColor(0.17f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch (example) {
    case 1:
        glutReshapeWindow(texture->getWidth(), texture->getHeight());
        gaussSingle();
        break;

    case 2:
        glutReshapeWindow(texture->getWidth(), texture->getHeight());
        gaussMultipass();
        break;

    case 3:
        glutReshapeWindow(texture->getWidth(), texture->getHeight());
        gaussSeparableMultipass();
        break;

    case 4:
        glutReshapeWindow(600, 600);
        waveEquation1();
        break;

    case 5:
        glutReshapeWindow(600, 600);
        waveEquation2();
        break;

    case 6:
        glutReshapeWindow(600, 600);
        waveEquation3();
        break;
    }

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (GLUT_LEFT_BUTTON == button && GLUT_UP == state) {
        addForce(x, y);
    }
}

void motion(int x, int y) {
    addForce(x, y);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {

    case 27:
    case 'q':
        exit(0);
        break;

    case 'r':
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

    case '5':
        example = 5;
        break;

    case '6':
        example = 6;
        break;

    case '+':
        npasses += 1;
        break;
    case '-':
        npasses = MAX(npasses - 1, 1);
        break;

    case ' ':
        resetWave();
        break;

    default:
        std::cout << "Unbinded key: " << (unsigned int) key << std::endl;
    }
    inputBuffer = 0;
    glutPostRedisplay();
}

void reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitContextVersion(3, 3);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("GPGPU 3. labor: glsl");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();

    return (0);
}
