#include <stdio.h>

// remove the ../include on official compilation, instead do -I include/
#include "../include/linlib.h"
#include "../include/renderlib.h"


DynamicPixelArray pxArr;
Scene testScene;
Camera testCamera;




Viewport testViewport;
Pt3 origin;
float viewportDistance;








DynamicPt3Array pt3Arr;

// cube
// Pt3 ptArr[8];
// int numPts = 8;

// piramyd
// Pt3 ptArr[4];
// int numPts = 4;




void initializeTestData() {

  pt3Arr = dynamicPt3Array();
  // cube
  addPt3(&pt3Arr, pt3(-0.5, 0.5, 1));
  addPt3(&pt3Arr, pt3(-0.5, -0.5, 1));
  addPt3(&pt3Arr, pt3(0.5, 0.5, 1));
  addPt3(&pt3Arr, pt3(0.5, -0.5, 1));
  addPt3(&pt3Arr, pt3(-0.5, 0.5, 2));
  addPt3(&pt3Arr, pt3(0.5, 0.5, 2));
  addPt3(&pt3Arr, pt3(-0.5, -0.5, 2));
  addPt3(&pt3Arr, pt3(0.5, -0.5, 2));

  // pyramid
  // ptArr[0] = pt3(-0.5, -0.5, 1);
  // ptArr[1] = pt3(0.5, -0.5, 1);
  // ptArr[2] = pt3(0, 0, 2);
  // ptArr[3] = pt3(0, 0.5, 1.5);

  testViewport = viewport(2, 2, 1024, 1024);
  viewportDistance = 1;
  origin = pt3(0, 0, 0);
  testCamera = camera(origin, viewportDistance, testViewport);


  // arrays are by default pointers (to mem)
  testScene = scene(&pt3Arr, testCamera);
  printf("init data");
}


// JS apis

// see pixels

DynamicPixelArray* getPixels() {
    return &pxArr;
}

// render the scene (key thing here :P)

void renderScene() {
    render(&pxArr, &testScene);
}

// point management

DynamicPt3Array* getPoints() {
    return &pt3Arr;
}

void addPoint(float x, float y, float z) {
  addPt3(&pt3Arr, pt3(x, y, z));
}

void removePoint(int index) {
  rmPt3(&pt3Arr, index);
}

void clearPoints() {
  clearPt3Array(&pt3Arr);
}

// init

void initialize() {
    initializeTestData();
    pxArr = dynamicPixelArray();
    pt3Arr = dynamicPt3Array();
}
