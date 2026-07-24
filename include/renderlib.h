#ifndef RENDERLIB_H
#define RENDERLIB_H
#include "linlib.h"

// Canvas.
// Will be assumed is centered on z-axis.
typedef struct {

  float wrldWidth, wrldHeight;
  float pxWidth, pxHeight;
  
} Viewport;


// Camera.
typedef struct {

  Pt3 eyeCoordinate;
  float canvasDistance;
  Viewport viewport;

  
} Camera;

// Scene; composition of everything.
typedef struct {

  Pt3 points; // array of points (later shape)
  Camera camera;
  
} Scene;


// METHODS

// render scene (intersect all points with plane and get pixels?)






    
#endif
