#include <stdio.h>

// remove the ../include on official compilation, instead do -I include/
#include "../include/linlib.h"
#include "../include/renderlib.h"


DynamicPixelArray pxArr;

Wireframe testWireframe;
Viewport testViewport;
float viewportDistance;
Pt3 origin;
Camera testCamera;
Scene testScene;

void initializeTestData() {

    testWireframe = wireframe();

    // vertices
    int v0 = addVertex(&testWireframe, pt3(-0.5, -0.5, 1));
    int v1 = addVertex(&testWireframe, pt3(-0.5,  0.5, 1));
    int v2 = addVertex(&testWireframe, pt3( 0.5,  0.5, 1));
    int v3 = addVertex(&testWireframe, pt3( 0.5, -0.5, 1));

    int v4 = addVertex(&testWireframe, pt3(-0.5,  0.5, 2));
    int v5 = addVertex(&testWireframe, pt3( 0.5,  0.5, 2));
    int v6 = addVertex(&testWireframe, pt3(-0.5, -0.5, 2));
    int v7 = addVertex(&testWireframe, pt3( 0.5, -0.5, 2));


    // front square
    connectVertices(&testWireframe, v0, v1);
    connectVertices(&testWireframe, v1, v2);
    connectVertices(&testWireframe, v2, v3);
    connectVertices(&testWireframe, v3, v0);


    // back square
    connectVertices(&testWireframe, v4, v5);
    connectVertices(&testWireframe, v5, v7);
    connectVertices(&testWireframe, v7, v6);
    connectVertices(&testWireframe, v6, v4);


    // connecting edges
    connectVertices(&testWireframe, v0, v6);
    connectVertices(&testWireframe, v1, v4);
    connectVertices(&testWireframe, v2, v5);
    connectVertices(&testWireframe, v3, v7);


    testViewport = viewport(2, 2, 1024, 1024);

    viewportDistance = 1;

    origin = pt3(0,0,0);

    testCamera = camera(
        origin,
        viewportDistance,
        testViewport
    );


    testScene = scene(
        &testWireframe,
        testCamera
    );
}


// JS apis

DynamicPixelArray* getProjectedVertices() {
  return &pxArr;
}

DynamicEdge3Array* getEdges() {
  return &testWireframe.edges;
}


// see pixels

// render the scene (key thing here :P)

void renderScene() {
    render(&pxArr, &testScene);
}

// init

void initialize() {
    pxArr = dynamicPixelArray();
    initializeTestData();
}
