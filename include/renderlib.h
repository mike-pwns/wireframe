#ifndef RENDERLIB_H
#define RENDERLIB_H
#include "linlib.h"

// Canvas.
// Will be assumed is centered on z-axis.
typedef struct {

  float wrldWidth, wrldHeight;
  float pxWidth, pxHeight;
  
} Canvas;


// Camera.
typedef struct {

  Point3 eyeCoordinate;
  float canvasDistance;
  Canvas canvas;

  
} Camera;

// Scene; composition of everything.
typedef struct {

  Point3 points; // array of points
  Camera camera;
  
} Scene;


// METHODS

// render scene (intersect all points with plane and get pixels?)






    
#endif
