#include <stdio.h>

// remove the ../include on official compilation, instead do -I include/
#include "../include/linlib.h"
#include "../include/renderlib.h"


CanvasPixelArray canvaspixels;
Scene testScene;
Camera testCamera;




Pt3 ptArr[3];
int numPts = 3;
Viewport testViewport;
Pt3 origin;
float viewportDistance;

void initializeTestData() {

  ptArr[0] = pt3(0, 0, 3);
  ptArr[1] = pt3(-0.5, 0.5, 100);
  ptArr[2] = pt3(1, 1, -3);
  testViewport = viewport(2, 2, 1024, 1024);
  viewportDistance = 1;
  origin = pt3(0, 0, 0);
  testCamera = camera(origin, viewportDistance, testViewport);


  // arrays are by default pointers (to mem)
  testScene = scene(ptArr, numPts, testCamera);
  printf("init data");
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

