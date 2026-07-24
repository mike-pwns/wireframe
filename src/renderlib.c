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
    canvasPixelArrPtr->array = realloc(canvasPixelArrPtr->array, canvasPixelArrPtr->length * sizeof(CanvasPixel));
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




















// render
/*

  for all points in scene
    if (point.z > viewport.z)
      get line from eye coord to point
      check intersection
      if intersection is in range of viewport (left edge < x < right edge; same for y)
        renderable; convert to pixel and save it to canvas accessibl

*/


// renders everything as it is
void  render(CanvasPixelArray* canvasPixelArrPtr, Scene* scenePtr) { // yeah screw that imma just pass len here

  // clear all previous pixels
  clear(canvasPixelArrPtr);
  
  // Unpack all stuff




  // Perform calcs and add to canvas


//   for (int i = 0; i < numPts; i++) {
// 
//     Pt3 pt = pointsArrPtr[i];
// 
//     
// 
//     
//   }
  

}
