#include <stdio.h>

// remove the ../include on official compilation, instead do -I include/
#include "../include/linlib.h"
#include "../include/renderlib.h"


CanvasPixelArray canvaspixels;
Scene testScene;
Camera testCamera;




Viewport testViewport;
Pt3 origin;
float viewportDistance;










// cube
Pt3 ptArr[8];
int numPts = 8;

// piramyd
// Pt3 ptArr[4];
// int numPts = 4;




void initializeTestData() {

  // cube
  ptArr[1] = pt3(-0.5, 0.5, 1);
  ptArr[0] = pt3(-0.5, -0.5, 1);
  ptArr[2] = pt3(0.5, 0.5, 1);
  ptArr[3] = pt3(0.5, -0.5, 1);
  ptArr[4] = pt3(-0.5, 0.5, 2);
  ptArr[6] = pt3(0.5, 0.5, 2);
  ptArr[5] = pt3(-0.5, -0.5, 2);
  ptArr[7] = pt3(0.5, -0.5, 2);

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
  testScene = scene(ptArr, numPts, testCamera);
  printf("init data");
}


// JS apis

CanvasPixelArray* getCanvasPixels() {
    return &canvaspixels;
}

void renderScene() {
    render(&canvaspixels, &testScene);
}

void initialize() {
    initializeTestData();
    canvaspixels = canvasPixelArray();
}



int main() {


  // testing intersection func

  // initialize scene
  // select figure
//   Vec3 dirVec = vec3(3, 2, -1);
//   normalizeVec3(&dirVec);
//   Pt3 ptLine = pt3(0, 1, 2);
//   Line3 line = line3(dirVec, ptLine);
// 
//   Vec3 normVec = vec3(2, 3, -1);
//   normalizeVec3(&normVec);
//   Pt3 ptPlane = pt3(0, 0, -4);
//   Plane plan = plane(normVec, ptPlane);
// 
//   Pt3 result = intersectionLinePlane(line, plan);
// 
//   printPt3(result);
  
  // test was successful!


  initializeTestData();
  printCanvasPixelArray(canvaspixels);
  printScene(testScene);

  render(&canvaspixels, &testScene);

  printCanvasPixelArray(canvaspixels);

  return 0;
}
