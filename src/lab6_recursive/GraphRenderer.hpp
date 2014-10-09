#pragma once

#include "shader.hpp"

#include <GL/glew.h>

class GraphRenderer {
protected:
    Shader* renderShader;
    float* adjacency;
    int nodeCnt;
    float* randPositions;
    float* edgeVertices;

    GLuint vertexArray;
    GLuint edgeVertexArray;
public:

    GraphRenderer(float* adjacency, int nodeCnt);
    ~GraphRenderer(void);
    void render();
    void getNodePos(int node, float& x, float& y);
    int getClosest(float x, float y);
};
