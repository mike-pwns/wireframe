#ifndef RENDERLIB_H
#define RENDERLIB_H
#include "linlib.h"


// ------------
// PRE SECTION
// ------------

// dynamic array!!!


// the actual pixel to draw things on
typedef struct {

  int x, y;
  
} CanvasPixel;
CanvasPixel canvasPixel(int x, int y);


// i just dont wanna deal w the scrappy solutions im thinking of; oughta be more *elegant*

typedef struct {
  int length;
  CanvasPixel* array;
  
} CanvasPixelArray; 
CanvasPixelArray canvasPixelArray();


void add(CanvasPixelArray* canvasPixelArrayPtr, CanvasPixel element); // adds to last
// void remove(CanvasPixelArray* arrayPtr, CanvasPixel element)
void clear(CanvasPixelArray* canvasPixelArrayPtr); // resets to len 0










// ------------
// PRE SECTION
// ------------













// Viewport.
// Will be assumed is centered on z-axis.
typedef struct {

  float wrldWidth, wrldHeight;
  float pxWidth, pxHeight;
  
} Viewport;
Viewport viewport(float wrldWidth, float wrldHeight, float pxWidth, float pxHeight);


// Camera.
typedef struct {

  Pt3 camOrigin; // for us (0, 0, 0)
  float viewportDistance;
  Viewport viewport;

  
} Camera;
Camera camera(Pt3 camOrigin, float viewportDistance, Viewport viewport);


// Scene; composition of everything.
typedef struct {

  Pt3 *points; // array of points (later shape)
  int numPts; // f u mr C im not playing that game again
  Camera camera;
  
} Scene;
Scene scene(Pt3 *points, int numPts, Camera camera);



// METHODS

// render scene (intersect all points with plane and get pixels?)

void render();





    
#endif
