#include "GraphRenderer.hpp"

#include <cstdlib>
#include <cmath>

GraphRenderer::GraphRenderer(float* adjacency, int nodeCnt) {
    this->adjacency = adjacency;
    this->nodeCnt = nodeCnt;

    randPositions = new float[nodeCnt * 2];
    for (int i = 0; i < nodeCnt * 2; ++i) {
        randPositions[i] = (float) rand() / (float) RAND_MAX * 2.0f - 1.0f;
    }

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * nodeCnt, randPositions, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint) 0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindVertexArray(0);

    edgeVertices = new float[nodeCnt * nodeCnt * 2 * 3];
    for (int i = 0; i < nodeCnt; ++i) {
        for (int j = 0; j < nodeCnt; ++j) {
            edgeVertices[(i * nodeCnt + j) * 2 * 3] = randPositions[i * 2];
            edgeVertices[(i * nodeCnt + j) * 2 * 3 + 1] = randPositions[i * 2 + 1];
            edgeVertices[(i * nodeCnt + j) * 2 * 3 + 3] = randPositions[j * 2];
            edgeVertices[(i * nodeCnt + j) * 2 * 3 + 4] = randPositions[j * 2 + 1];
            if (adjacency[i * nodeCnt + j] > 0) {
                edgeVertices[(i * nodeCnt + j) * 2 * 3 + 2] = (1.0 - adjacency[i * nodeCnt + j]) * 0.5;
                edgeVertices[(i * nodeCnt + j) * 2 * 3 + 5] = (1.0 - adjacency[j * nodeCnt + i]) * 0.5;
            } else {
                edgeVertices[(i * nodeCnt + j) * 2 * 3 + 2] = 0;
                edgeVertices[(i * nodeCnt + j) * 2 * 3 + 5] = 0;
            }
        }
    }

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * 3 * nodeCnt * nodeCnt, edgeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint) 0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindVertexArray(0);

    renderShader = new Shader("../src/lab6_recursive/shaders/nodeRender.vert",
            "../src/lab6_recursive/shaders/nodeRender.frag");

}

GraphRenderer::~GraphRenderer(void) {
}

void GraphRenderer::getNodePos(int node, float& x, float& y) {
    x = randPositions[node * 2];
    y = randPositions[node * 2 + 1];
}

int GraphRenderer::getClosest(float x, float y) {
    float dist = 10000;
    int closest = -1;

    for (int i = 0; i < nodeCnt; ++i) {
        float d = sqrt(
                (x - randPositions[i * 2]) * (x - randPositions[i * 2]) + (y - randPositions[i * 2 + 1])
                        - (y - randPositions[i * 2 + 1]));
        if (d < dist) {
            dist = d;
            closest = i;
        }
    }
    return closest;
}

void GraphRenderer::render() {
    glPointSize(10);

    renderShader->enable();
    glBindVertexArray(vertexArray);
    renderShader->bindAttribLocation(0, "position");
    glDrawArrays(GL_POINTS, 0, nodeCnt);
    glBindVertexArray(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    renderShader->bindAttribLocation(0, "position");
    glDrawArrays(GL_LINES, 0, nodeCnt * nodeCnt * 2);
    glBindVertexArray(0);
    glDisable(GL_BLEND);

    renderShader->disable();

}
