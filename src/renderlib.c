#include <stdio.h>
#include <stdlib.h>
#include "../include/renderlib.h"
#include "../include/linlib.h"
#include <math.h> // TODO  i should prolly just use the pi from this?

// ------------
// PRE SECTION
// ------------

// damnnnn youuuu and your stupidly simple fixed array ccccc!!!!!!!!!!! now i gotta figure out how to make dynamic array!!! no more fun and games like in python :(


CanvasPixelArray canvasPixelArray() {
  return (CanvasPixelArray) {

    .length = 0,
    .array = NULL
    
  };
}

void add(CanvasPixelArray* canvasPixelArrPtr, CanvasPixel newElement) {

  // update len var
  canvasPixelArrPtr->length += 1;

  // if new len is 1 (first element added), malloc
  if (canvasPixelArrPtr->length == 1) {
    canvasPixelArrPtr->array = malloc(1 * sizeof(CanvasPixel));
  }

  // if not 1st and like 41st, just ralloc that thang
  else {
    canvasPixelArrPtr->array = realloc(canvasPixelArrPtr->array, canvasPixelArrPtr->length * sizeof(CanvasPixel)); // i remember something about realloc being bad, idk for this case it should be fine
  }

  // assign new element
  canvasPixelArrPtr->array[canvasPixelArrPtr->length - 1] = newElement;

}

// just reet the thing (make sure to free old mem!!! not just fuget abaut it)
void clear(CanvasPixelArray* canvasPixelArrPtr) {
  canvasPixelArrPtr->length = 0;
  free(canvasPixelArrPtr->array);
  canvasPixelArrPtr->array = NULL;
}




// ------------
// PRE SECTION
// ------------




#include "../include/renderlib.h"

// --------------------
// CanvasPixel
// --------------------

CanvasPixel canvasPixel(int x, int y) {
    return (CanvasPixel){
        .x = x,
        .y = y
    };
}

// --------------------
// Viewport
// --------------------

Viewport viewport(float wrldWidth,
                  float wrldHeight,
                  int pxWidth,
                  int pxHeight) {

    return (Viewport){
        .wrldWidth = wrldWidth,
        .wrldHeight = wrldHeight,
        .pxWidth = pxWidth,
        .pxHeight = pxHeight
    };
}

// --------------------
// Camera
// --------------------

Camera camera(Pt3 camOrigin,
              float viewportDistance,
              Viewport viewport) {

    return (Camera){
        .camOrigin = camOrigin,
        .viewportDistance = viewportDistance,
        .viewport = viewport
    };
}

Scene scene(Pt3 *points, int numPts, Camera camera) {
    return (Scene){
        .points = points,
        .numPts = numPts,
        .camera = camera
    };
}




CanvasPixel ptToPx(Viewport viewport, Pt3 pt) {
    // move it over so that it starts from (0, 0) in top left
    // then scale it down to fit viewport

    int x = (int)((pt.x + viewport.wrldWidth * 0.5f) *
                  (viewport.pxWidth / viewport.wrldWidth));

    int y = (int)((viewport.wrldHeight * 0.5f - pt.y) *
                  (viewport.pxHeight / viewport.wrldHeight));

    return canvasPixel(x, y);
}






















// renders everything as it is
void  render(CanvasPixelArray* canvasPixelArrPtr, Scene* scenePtr) { 

  // clear all previous pixels
  clear(canvasPixelArrPtr); 

  // TESTING!!!
  // add(canvasPixelArrPtr, canvasPixel(1, 2));
  // printCanvasPixelArray(*canvasPixelArrPtr);


  // ACTUAL STUFF
  
  // get plane (normal is z axis, known point is (0, 0, viewportDistance))

  Plane viewportPlane = plane(vec3(0, 0, 1), pt3(0, 0, scenePtr->camera.viewportDistance));

  // Perform calcs and add to canvas

  for (int i = 0; i < scenePtr->numPts; i++) {
  
    Pt3 pt = scenePtr->points[i];

    // create line (vector) --> this is the direction vector.

    Vec3 dirvec = vec3(
      pt.x - scenePtr->camera.camOrigin.x,
      pt.y - scenePtr->camera.camOrigin.y,
      pt.z - scenePtr->camera.camOrigin.z
    );

    // normalize it too (in case the point is like super far away, milly-billy-trilly units; thatd be bad for computation)
    normalizeVec3(&dirvec);


    /*
      bit of optimization logic; derived from the idea of rays! (i honestyly got no clue whta they are i just imagine it to be something-whatever)

    if the resulting vector is facing AWAY (or is IN LINE with the point on the z axis, hence = 0)
    then the iterated point is BEHIND the camera, it shouldnt show up on the viewport even if it intersects. 

    i did just if statements for this later on, then realized and put the condition here

    */

    
    if (dirvec.z <= 0) {
      continue;
    }

    // build a line (for the point could use either cam orig or iterated pt dont matter)
    Line3 line = line3(dirvec, scenePtr->camera.camOrigin);

    // fun part now!
    Pt3 intersectionPoint = intersectionLinePlane(line, viewportPlane);

    // Now just do some checks before proceeding:

    // if returned (0, 0, 0), its faulty (line is parallel. dont do anything). 
    // All results theoretically should have a z thats the same as viewportDistance). 
    // Do something with that? ^


    // CHECKED THIS WITH CONDITION ABOVE (i think)
    // if (intersectionPoint.x == 0 && intersectionPoint.y == 0 && intersectionPoint.z == 0) {
    //   continue;
    // }

    // if the intersection does not exist within the bounds of the viewport, skip the point
  if (
      !(

        // check x range
        (scenePtr->camera.camOrigin.x - 0.5f * scenePtr->camera.viewport.wrldWidth) <= intersectionPoint.x &&
        intersectionPoint.x <= (scenePtr->camera.camOrigin.x + 0.5f * scenePtr->camera.viewport.wrldWidth) &&


        // check y range
        scenePtr->camera.camOrigin.y - 0.5f * scenePtr->camera.viewport.wrldHeight <= intersectionPoint.y &&
        intersectionPoint.y <= scenePtr->camera.camOrigin.y + 0.5f * scenePtr->camera.viewport.wrldHeight)
  ) {
      continue;
  }

    // convert to px and add
    add(canvasPixelArrPtr, ptToPx(scenePtr->camera.viewport, intersectionPoint));
    

    
  }

}



















void printCanvasPixelArray(CanvasPixelArray arr) {

    printf("CanvasPixelArray {\n");
    printf("  length: %d\n", arr.length);
    printf("  pixels:\n");

    for (int i = 0; i < arr.length; i++) {
        printf("    [%d] (%d, %d)\n",
               i,
               arr.array[i].x,
               arr.array[i].y);
    }

    printf("}\n");
}

void printScene(Scene scene) {

    printf("Scene {\n");

    printf("  numPts: %d\n", scene.numPts);

    printf("  points:\n");
    for (int i = 0; i < scene.numPts; i++) {
        printf("    [%d] ", i);
        printPt3(scene.points[i]);
    }

    printf("  camera:\n");

    printf("    origin: ");
    printPt3(scene.camera.camOrigin);

    printf("    viewportDistance: %f\n",
           scene.camera.viewportDistance);

    printf("    viewport:\n");
    printf("      worldWidth : %f\n",
           scene.camera.viewport.wrldWidth);
    printf("      worldHeight: %f\n",
           scene.camera.viewport.wrldHeight);
    printf("      pixelWidth : %d\n",
           scene.camera.viewport.pxWidth);
    printf("      pixelHeight: %d\n",
           scene.camera.viewport.pxHeight);

    printf("}\n");
}
  


