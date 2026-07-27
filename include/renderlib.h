#ifndef RENDERLIB_H
#define RENDERLIB_H
#include "linlib.h"


// ------------
// PRE SECTION
// ------------

// dynamic array!!!


typedef struct {

  Pt3* data;
  int numElements;
  int capacity;
  
} DynamicPt3Array;
DynamicPt3Array dynamicPt3Array();
void addPt3(DynamicPt3Array *arr, Pt3 pt);
void rmPt3(DynamicPt3Array *arr, int index);
void clearPt3Array(DynamicPt3Array *arr);







// the actual pixel to draw things on
typedef struct {
  int x, y;  
} Pixel;
Pixel pixel(int x, int y);


// i just dont wanna deal w the scrappy solutions im thinking of; oughta be more *elegant*

typedef struct {
  Pixel* data;
  int numElements;
  int capacity;
  
} DynamicPixelArray; 
DynamicPixelArray dynamicPixelArray();
void add(DynamicPixelArray *arr, Pixel pixel); // adds to last
void clear(DynamicPixelArray *arr); // resets to len 0










// ------------
// PRE SECTION
// ------------













// Viewport.
// Will be assumed is centered on z-axis.
typedef struct {

  float wrldWidth, wrldHeight;
  int pxWidth, pxHeight;
  
} Viewport;
Viewport viewport(float wrldWidth, float wrldHeight, int pxWidth, int pxHeight);


// Camera.
typedef struct {

  Pt3 camOrigin; // for us (0, 0, 0)
  float viewportDistance;
  Viewport viewport;

  
} Camera;
Camera camera(Pt3 camOrigin, float viewportDistance, Viewport viewport);


// Scene; composition of everything.
typedef struct {

  DynamicPt3Array *pt3Arr;
  Camera camera;
} Scene;
Scene scene(DynamicPt3Array *pt3Arr, Camera camera);



// --------------------
// Debug / Printing
// --------------------

void printDynamicPixelArray(DynamicPixelArray arr);
void printScene(Scene scene);



// thing

int worldToPixel(float wrldX, float worldY);

// METHODS

// render scene (intersect all points with plane and get pixels?)

void render(DynamicPixelArray* arr, Scene* scenePtr);





    
#endif
