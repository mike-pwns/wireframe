#ifndef RENDERLIB_H
#define RENDERLIB_H
#include "linlib.h"


//  ||====================================================
//  ||
//  || STRUCTS |||||||||||||||||||||||||||||||||||||||||||
//  || 
//  ||====================================================


//  ||----------------------------------------------------
//  ||
//  || MATH++ ||||||||||||||||||||||||||||||||||||||||||||
//  || 
//  || Camera, Viewport. Scene. Add-ons to math that 
//  || pertain to this project.
//  || 
//  || We're getting to the more "comp sci" side of 
//  || things here :P
//  || 
//  ||----------------------------------------------------


//  ||====================================================
//  || EDGE ||||||||||||||||||||||||||||||||||||||||||||||
//  ||====================================================


// Edge is mathematically between 2 points.
// Here it is between 2 points as references of index.
// (Index is in reference to pt3DynamicArray)
typedef struct {

  int startIndex;   
  int endIndex;
  
} Edge3;
Edge3 edge3(int startIndex, int endIndex);

// Dynamic array for Edge3.
typedef struct {

  Edge3* data;
  int numElements;
  int capacity;

} DynamicEdge3Array;
DynamicEdge3Array dynamicEdge3Array();
void addEdge3(DynamicEdge3Array *arr, Edge3 edge3);
void rmEdge3(DynamicEdge3Array *arr, int index);
void clearEdge3Array(DynamicEdge3Array *arr);


//  ||====================================================
//  || WIREFRAME |||||||||||||||||||||||||||||||||||||||||
//  ||====================================================


// *Fun fact* This structure - wireframe - was the whole inspiration of this project.

// Wireframe is just a collection of verts and edges.
// This makes up a shape with connected edges.
typedef struct {

  DynamicPt3Array vertices; 
  DynamicEdge3Array edges;

} Wireframe;
Wireframe wireframe();
int addVertex(Wireframe* wireframePtr, Pt3 pt); // Returns the index of the vertex added (good for edge building).
void connectVertices(Wireframe* wireframePtr, int startIndex, int endIndex); // Adds an edge between 2 pts.
void clearWireframe(Wireframe* wireframePtr); // Clears the dynamic arrays.


//  ||----------------------------------------------------
//  ||
//  || PIXEL-MANAGEMENT ||||||||||||||||||||||||||||||||||
//  || 
//  || Camera, Viewport. Scene.
//  || 
//  ||----------------------------------------------------


//  ||====================================================
//  || PIXEL |||||||||||||||||||||||||||||||||||||||||||||
//  ||====================================================


// Pixel is used to define the coordinates on a 2D canvas.
typedef struct {

  int x; 
  int y;  

} Pixel;
Pixel pixel(int x, int y);

// Dynamic array for Pixel.
typedef struct {

  Pixel* data;
  int numElements;
  int capacity;

} DynamicPixelArray; 
DynamicPixelArray dynamicPixelArray();
void add(DynamicPixelArray *arr, Pixel pixel); 
void clear(DynamicPixelArray *arr); 


//  ||====================================================
//  || RENDERED PIXEL ||||||||||||||||||||||||||||||||||||
//  ||====================================================


// (May be unnecessary but was cleaner this way imo)
// RenderedPixel is like the final pixel that gets presented to js.
// Main idea is that it accounts for edge-cases (laugh now) like clipping.
typedef struct {

  Pixel pixel;
  int isInFrontOfCamera; 

} RenderedPixel;
RenderedPixel renderedPixel(Pixel pixel, int isInFrontOfCamera);

// Dynamic array for RenderedPixel.
typedef struct {

  RenderedPixel* data;
  int numElements;
  int capacity;

} DynamicRenderedPixelArray;
DynamicRenderedPixelArray dynamicRenderedPixelArray();
void addRenderedPixel(DynamicRenderedPixelArray *arr, RenderedPixel pixel);
void clearRenderedPixelArray(DynamicRenderedPixelArray *arr);


//  ||====================================================
//  || RENDERED LINE  ||||||||||||||||||||||||||||||||||||
//  ||====================================================


// Just a collection that tells js "point here to this one".
// Very neat for the canvas api when drawing lines.
typedef struct {

  Pixel startPixel;
  Pixel endPixel;

} RenderedLine;
RenderedLine renderedLine(Pixel startPixel, Pixel endPixel);

// Dynamic Array for RenderedLine.
typedef struct {

  RenderedLine* data;
  int numElements;
  int capacity;

} DynamicRenderedLineArray;
DynamicRenderedLineArray dynamicRenderedLineArray();
void addRenderedLine(DynamicRenderedLineArray *arr, RenderedLine line);
void clearRenderedLineArray(DynamicRenderedLineArray *arr);


//  ||====================================================
//  || RENDERED RESULT |||||||||||||||||||||||||||||||||||
//  ||====================================================


// The final product JS sees. 
// Includes the pixels and lines that will be drawn on the canvas.
typedef struct {

  DynamicRenderedPixelArray pixels;
  DynamicRenderedLineArray lines;

} RenderedResult;
RenderedResult renderedResult();


//  ||----------------------------------------------------
//  ||
//  || PROJECTION SETUP ||||||||||||||||||||||||||||||||||
//  || 
//  || Camera, Viewport. Scene.
//  || 
//  ||----------------------------------------------------


// Viewport; the "intersect-screen".
typedef struct {

  float wrldWidth, wrldHeight;
  int pxWidth, pxHeight;

} Viewport;
Viewport viewport(float wrldWidth, float wrldHeight, int pxWidth, int pxHeight);

// Camera - the whole rig: distance, viewport, "perspective point"/"eye".
// Also includes transformation for cam moving feature.
typedef struct {

  Pt3 camOrigin; 
  float viewportDistance;
  Viewport viewport;
  Transformation transformation;

} Camera;
Camera camera(Pt3 camOrigin, float viewportDistance, Viewport viewport, Transformation transformation);

// Scene; composition of everything in "vectorspace".
typedef struct {

  Wireframe *wireframe;
  Camera camera;
  
} Scene;
Scene scene(Wireframe* wireframe, Camera camera);


//  ||----------------------------------------------------
//  ||
//  || PRINT FORMATTING  |||||||||||||||||||||||||||||||||
//  || 
//  || Convenient printing functions for debugging.
//  || 
//  ||----------------------------------------------------


void printDynamicPixelArray(DynamicPixelArray arr);
void printScene(Scene scene);


//  ||----------------------------------------------------
//  ||
//  || CONVERTING UNITS  |||||||||||||||||||||||||||||||||
//  || 
//  || World -> Canvas, and vice versa. 
//  || 
//  ||----------------------------------------------------


Pixel ptToPx(Viewport viewport, Pt3 pt);
int worldToPixel(float wrldX, float worldY);


//  ||====================================================
//  ||
//  || METHODS |||||||||||||||||||||||||||||||||||||||||||
//  || 
//  ||====================================================


//  ||----------------------------------------------------
//  ||
//  || RENDER  |||||||||||||||||||||||||||||||||||||||||||
//  || 
//  || The "snapshot" of a world function; whole project
//  || leads to this one function. 
//  || 
//  ||----------------------------------------------------


// Saves result in provided RenderedResult.
void render(Scene* scenePtr, RenderedResult* outputPtr);


//  ||----------------------------------------------------
//  ||
//  || MODEL BUILDERS  |||||||||||||||||||||||||||||||||||
//  || 
//  || Includes premade models: CUBE,
//  || 
//  || Note: these are AI-generated.  
//  || 
//  ||----------------------------------------------------


void CUBE(Wireframe* model);


//  ||----------------------------------------------------
//  ||
//  || CUSTOM MODELLER FUNCS  ||||||||||||||||||||||||||||
//  || 
//  || For custom model making.
//  || 
//  ||----------------------------------------------------
    
#endif
