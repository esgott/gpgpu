#include <GL/glew.h>
#include <GL/freeglut.h>

#include "framebuffer.hpp"
#include "shader.hpp"
#include "quad.hpp"
#include "matrix4x4.hpp"
#include "camera.hpp"

#include <iostream>
#include <cstring>

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

int windowWidth = 600;
int windowHeight = 600;

Quad* fullscreenQuad;
Shader* simpleShader;

bool keysPressed[256];
Camera camera;

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

    fullscreenQuad = new Quad();
    simpleShader = new Shader("../src/lab5/shaders/raydir.vert", "../src/lab5/shaders/raytrace.frag");

    memset(keysPressed, 0, sizeof(bool) * 256);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void display() {
    glClearColor(0.17f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutReshapeWindow(600, 600);
    simpleShader->enable();

    fullscreenQuad->render(simpleShader);
    simpleShader->disable();

    glutSwapBuffers();
}

void animate() {
    static float lastTime = 0.0;
    long timeInMilliSecs = glutGet(GLUT_ELAPSED_TIME);
    float timeNow = timeInMilliSecs / 1000.0f;
    float deltaTime = timeNow - lastTime;
    lastTime = timeNow;

    camera.control(deltaTime, keysPressed);

    glutPostRedisplay();
}

void keyDown(unsigned char key, int x, int y) {
    keysPressed[key] = true;
}

void keyUp(unsigned char key, int x, int y) {
    keysPressed[key] = false;
    switch (key) {
    case 27:
        exit(0);
        break;

    }
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN)
            camera.startDrag(x, y);
}

void mouseMove(int x, int y) {
    camera.drag(x, y);
}

void reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
    camera.setAspectRatio((float) width / height);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitContextVersion(3, 3);
    glutInitContextFlags(GLUT_CORE_PROFILE | GLUT_DEBUG);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("GPGPU 6. labor: raytracing");

    init();

    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);

    glutMainLoop();

    return (0);
}
