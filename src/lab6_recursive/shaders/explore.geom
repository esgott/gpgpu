#version 130
#extension GL_EXT_geometry_shader4 : enable

uniform sampler2D adjacency;
uniform sampler2D shortestPath; //shortest path length + path dir
out vec4 nodedata;

void main(void) {
    //properties of the current graph node
    float nodeCount = textureSize(shortestPath, 0).x;
    vec4 vertexdata = gl_PositionIn[0];
    int nodeID = int(vertexdata.x);
    vec4 storedNodeData = texelFetch(shortestPath, ivec2(nodeID, 0), 0);
    float pathLen = storedNodeData.y;

    //this should be the start node
    if(vertexdata.w == 0) {
    ////
    // TODO emit vertex with correct position and nodedata value (valid flag should be set to 0)
    ////
    }

    ////
    // TODO visit all neighbor nodes (all nodes) and emit vertices for them if needed (a shorter path is found to them)
    ////
}
