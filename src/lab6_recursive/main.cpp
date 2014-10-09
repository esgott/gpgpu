#include "framebuffer.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "quad.hpp"
#include "GraphRenderer.hpp"

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

int windowWidth = 600;
int windowHeight = 600;

int nodeCnt = 8;
float* data;

Framebuffer* nodes;
GLuint adjacency;
Quad* fullscreenQuad;
Shader* exploreShader;
Shader* pathShader;

GLuint streamoutBufffer[2];
GLuint outputQuery;

int startNode = 0;
int endNode = 1;

GraphRenderer* graphrenderer;

bool startChanged = true;
bool endChanged = true;

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
    glGetError();

    fullscreenQuad = new Quad();
    exploreShader = new Shader("../src/lab6_recursive/shaders/explore.vert",
            "../src/lab6_recursive/shaders/explore.frag", "../src/lab6_recursive/shaders/explore.geom");

    data = new float[nodeCnt * nodeCnt];
    for (int i = 0; i < nodeCnt; ++i) {
        for (int j = 0; j < nodeCnt; ++j) {
            if (i == j)
                data[i * nodeCnt + j] = 0;
            else
                data[i * nodeCnt + j] = (float) rand() / (float) (RAND_MAX);
        }
    }
    graphrenderer = new GraphRenderer(data, nodeCnt);

    ////
    // TODO: move adjacency data to a 2D texture (adjacency), use nearest filtering
    // TODO: create framebuffer for node data (Nx1 size texture)
    // TODO: 2 buffers (streamoutBufffer) for vertex transform feedback, size can be : N * N * 2 * sizeof(float)
    // TODO: create query object (outputQuery)
    ////
}

void draw() {
    if (startChanged) {

        ////
        // TODO: set nodes texture as rendertarget and clear to 0
        // TODO: enable shader, bind texture variables to it
        // TODO: bind transform feedback buffer, begin transform feedback, begin query
        // TODO: draw a single point with start node id (vertex position = (id,0,0,0))
        // TODO: end query, end feedback, wait till query is ready and read it
        // first, initialization step is ready
        ////

        ////
        // TODO: create a loop: while geometry shader has non zero output
        // TODO: inside the loop do the same as above BUT: render not only a single point, but points from the buffer previously saved by the geometry shader
        // don't forget to alternate the roles of the feedback buffer and the draw buffer
        //
        // TODO: after loop disable shader and rendertarget
        ///

    }

    glViewport(0, 0, windowWidth, windowHeight);

    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    graphrenderer->render();

    //draw start and end points
    glBegin(GL_POINTS);
    glColor3f(0, 0, 1);
    float x0, y0, x1, y1;
    graphrenderer->getNodePos(startNode, x0, y0);
    glVertex3f(x0, y0, 0);
    glColor3f(0, 1, 0);
    graphrenderer->getNodePos(endNode, x1, y1);
    glVertex3f(x1, y1, 0);
    glEnd();

    //draw path
    static float* pathData = new float[nodeCnt * 4];
    for (int i = 0; i < nodeCnt * 4; ++i)
        pathData[i] = 0;

    ////
    // TODO read back the nodes texture and put the contents to pathData
    ////

    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    float x, y;
    int node = endNode;
    while (node != startNode) {
        if (pathData[node * 4 + 3] == 0)
            break;
        graphrenderer->getNodePos(node, x, y);
        glVertex3f(x, y, 0);
        node = pathData[node * 4 + 2];
        //printf("newnode: %i \n", node);
    }
    graphrenderer->getNodePos(node, x, y);
    glVertex3f(x, y, 0);
    glEnd();

    glFinish();
}

void mouse(int button, int state, int x, int y) {
    if (GLUT_LEFT_BUTTON == button && GLUT_UP == state) {
        startNode = graphrenderer->getClosest((float) x / (float) windowWidth * 2.0f - 1.0f,
                -1 * ((float) y / (float) windowHeight * 2.0f - 1.0f));
        startChanged = true;
        glutPostRedisplay();
    }
    if (GLUT_RIGHT_BUTTON == button && GLUT_UP == state) {
        endNode = graphrenderer->getClosest((float) x / (float) windowWidth * 2.0f - 1.0f,
                -1 * ((float) y / (float) windowHeight * 2.0f - 1.0f));
        glutPostRedisplay();
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitContextVersion(3, 0);
    glutInitContextFlags(GLUT_CORE_PROFILE | GLUT_DEBUG);
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("GPGPU 3. labor: glsl");

    init();

    glutDisplayFunc(draw);
    glutMouseFunc(mouse);
    glutMainLoop();

    return (0);
}
