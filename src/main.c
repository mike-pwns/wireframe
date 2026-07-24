#include <stdio.h>

// remove the ../include on official compilation, instead do -I include/
#include "../include/linlib.h"
#include "../include/renderlib.h"

Scene scene;
CanvasPixel canvaspixels;

int main() {


  // testing intersection func

  // initialize scene
  // select figure
  Vec3 dirVec = vec3(3, 2, -1);
  normalizeVec3(&dirVec);
  Pt3 ptLine = pt3(0, 1, 2);
  Line3 line = line3(dirVec, ptLine);

  Vec3 normVec = vec3(2, 3, -1);
  normalizeVec3(&normVec);
  Pt3 ptPlane = pt3(0, 0, -4);
  Plane plan = plane(normVec, ptPlane);

  Pt3 result = intersectionLinePlane(line, plan);

  printPt3(result);
  
  // test was successful!

  return 0;
}

// static Pt3 ptArr[2];
// static int numPts = 2;


void initializeTestData() {

 // ptArr[0] = pt3(0, 0, 3);
 // ptArr[1] = pt3(-1, -1, 3);

}
