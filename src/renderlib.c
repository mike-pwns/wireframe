#include <stdio.h>
#include <stdlib.h>
#include "../include/renderlib.h"
#include "../include/linlib.h"
#include <math.h> 


//  ||====================================================
//  ||
//  || "CONSTRUCTORS" AND DYNAMIC ARRAYS |||||||||||||||||
//  || 
//  ||====================================================


//  ||----------------------------------------------------
//  ||
//  || CONSTRUCTORS (PART 1)  ||||||||||||||||||||||||||||
//  || 
//  || Base constructors that dont rely on dynamic arrays.
//  || 
//  ||----------------------------------------------------


//  ||====================================================
//  || WIREFRAME COMPOSITION |||||||||||||||||||||||||||||
//  ||====================================================


// Edge; line between 2 vertexes in 3D space.
Edge3 edge3(int startIndex, int endIndex) {
  return (Edge3) {
    .startIndex = startIndex,
    .endIndex = endIndex
  };
}

// + Vertex should be here, but since vertexes are
//   just points (ahem Pt3), it'd be redundant here.


//  ||====================================================
//  || WORLD COMPOSITION |||||||||||||||||||||||||||||||||
//  ||====================================================


// Viewport is like the screen we see the world through.
Viewport viewport(float wrldWidth, float wrldHeight, int pxWidth, int pxHeight) {
    return (Viewport){
        .wrldWidth = wrldWidth,
        .wrldHeight = wrldHeight,
        .pxWidth = pxWidth,
        .pxHeight = pxHeight
    };
}

// Actual camera object (combination of all things.)
Camera camera(Pt3 camOrigin, float viewportDistance, Viewport viewport, Transformation transformation) {
    return (Camera){
        .camOrigin = camOrigin,
        .viewportDistance = viewportDistance,
        .viewport = viewport,
        .transformation = transformation
    };
}

// Scene is the world itself; what exists and how we see it.
// This is 1 of 2 major components that make up the project.
Scene scene(Wireframe* wireframe, Camera camera) {
    return (Scene){
        .wireframe = wireframe,
        .camera = camera
    };
}


//  ||====================================================
//  || PIXELS AND VISIBLE OUTPUT |||||||||||||||||||||||||
//  ||====================================================


// Pixel is just struct for organization to send to JS neatly.
Pixel pixel(int x, int y) {
    return (Pixel){
        .x = x,
        .y = y
    };
}

// Note: The rendered series of structs is just for
//       output - purely for JS to see and put onto canvas.


// Rendered pixel just says "yo this pixel exists", draw (or dont) draw it!
// The is in front is primarily used as conditions for  edges.
RenderedPixel renderedPixel(Pixel pixel, int isInFrontOfCamera) {
  return (RenderedPixel) {
    .pixel = pixel,
    .isInFrontOfCamera = isInFrontOfCamera
  };
}

// RenderedLine is just for where to draw lines on the canvas.
RenderedLine renderedLine(Pixel startPixel, Pixel endPixel) {
  return (RenderedLine) {
    .startPixel = startPixel,
    .endPixel = endPixel
  };
}


//  ||----------------------------------------------------
//  ||
//  || DYNAMIC ARRAYS & FRIENDS (METHODS)  |||||||||||||||
//  || 
//  || Just dynamic arrays for necessary objects and 
//  || their respective add/remove/etc implementations. 
//  || 
//  || Note: line by line comment is in the linlib.c, not
//  ||       repeating it all 4-6 times same thing.
//  ||       
//  || Note: The implementation is that of ArrayList in
//  ||       Java (i think - thats what I was told).
//  || 
//  ||----------------------------------------------------


//  ||====================================================
//  || PIXEL STRUCT ARRAY ||||||||||||||||||||||||||||||||
//  ||====================================================


DynamicPixelArray dynamicPixelArray() {
  return (DynamicPixelArray) {
    .data = malloc(sizeof(Pixel)),
    .numElements = 0,
    .capacity = 1
  };
}

void addPixel(DynamicPixelArray *arr, Pixel pixel) {

  if (arr->numElements == arr->capacity) {

    Pixel* temp = malloc((arr->capacity * 2) * sizeof(Pixel));

    for (int i = 0; i < arr->capacity; i++) {
      temp[i] = arr->data[i];
    }

    free(arr->data);

    arr->capacity *= 2;

    arr->data = temp;
    
  }

  arr->data[arr->numElements] = pixel;
  arr->numElements++;  

}

void clearPixelArray(DynamicPixelArray *arr) {

  free(arr->data);

  arr->data = malloc(sizeof(Pixel));
  arr->numElements = 0;
  arr->capacity = 1;  

}


//  ||====================================================
//  || EDGE3 STRUCT ARRAY ||||||||||||||||||||||||||||||||
//  ||====================================================


DynamicEdge3Array dynamicEdge3Array() {
  return (DynamicEdge3Array) {
    .data = malloc(sizeof(Edge3)),
    .numElements = 0,
    .capacity = 1
  };
}

void addEdge3(DynamicEdge3Array *arr, Edge3 edge3) {

  if (arr->numElements == arr->capacity) {

    Edge3* temp = malloc((arr->capacity * 2) * sizeof(Edge3));

    for (int i = 0; i < arr->capacity; i++) {
      temp[i] = arr->data[i];
    }

    free(arr->data);

    arr->capacity *= 2;
    
    arr->data = temp;
    
  }

  arr->data[arr->numElements] = edge3;
  arr->numElements++;  
  
}

void rmEdge3(DynamicEdge3Array *arr, int index) { 

  if (index < 0 || index >= arr->numElements) {
      return;
  }

  Edge3* temp = malloc(arr->capacity * sizeof(Edge3));

  int removed = 0;

  for (int i = 0; i < arr->numElements; i++) {      

    if (i == index) {
      removed = 1;
    }

    else {
      if (removed) {
        temp[i-1] = arr->data[i];
      }
      else {
        temp[i] = arr->data [i];
      }
    }
  }

  free(arr->data);

  arr->data = temp;
  arr->numElements--;  
    
}

void clearEdge3Array(DynamicEdge3Array *arr) {

  free(arr->data);

  arr->data = malloc(sizeof(Edge3));
  arr->numElements = 0;
  arr->capacity = 1;
  
}


//  ||====================================================
//  || DYNAMIC RENDERED PIXEL STRUCT ARRAY |||||||||||||||
//  ||====================================================


DynamicRenderedPixelArray dynamicRenderedPixelArray() {

  return (DynamicRenderedPixelArray) {
    .data = malloc(sizeof(RenderedPixel)),
    .numElements = 0,
    .capacity = 1
  };

}

void addRenderedPixel(DynamicRenderedPixelArray *arr, RenderedPixel pixel) {

  if (arr->numElements == arr->capacity) {

    RenderedPixel* temp = malloc((arr->capacity * 2) * sizeof(RenderedPixel));

    for (int i = 0; i < arr->capacity; i++) {
      temp[i] = arr->data[i];
    }

    free(arr->data);

    arr->capacity *= 2;
    arr->data = temp;

  }

  arr->data[arr->numElements] = pixel;
  arr->numElements++;

}

void clearRenderedPixelArray(DynamicRenderedPixelArray *arr) {

  free(arr->data);

  arr->data = malloc(sizeof(RenderedPixel));
  arr->numElements = 0;
  arr->capacity = 1;

}


//  ||====================================================
//  || DYNAMIC RENDERED LINE  STRUCT ARRAY |||||||||||||||
//  ||====================================================


DynamicRenderedLineArray dynamicRenderedLineArray() {
  return (DynamicRenderedLineArray) {
    .data = malloc(sizeof(RenderedLine)),
    .numElements = 0,
    .capacity = 1
  };
}

void addRenderedLine(DynamicRenderedLineArray *arr, RenderedLine line) {

  if (arr->numElements == arr->capacity) {

    RenderedLine* temp = malloc((arr->capacity * 2) * sizeof(RenderedLine));

    for (int i = 0; i < arr->capacity; i++) {
      temp[i] = arr->data[i];
    }

    free(arr->data);

    arr->capacity *= 2;
    arr->data = temp;

  }

  arr->data[arr->numElements] = line;
  arr->numElements++;

}

void clearRenderedLineArray(DynamicRenderedLineArray *arr) {

  free(arr->data);

  arr->data = malloc(sizeof(RenderedLine));
  arr->numElements = 0;
  arr->capacity = 1;

}



//  ||----------------------------------------------------
//  ||
//  || CONSTRUCTORS (PART 2)  ||||||||||||||||||||||||||||
//  || 
//  || Base constructors rely on dynamic arrays.
//  || 
//  ||----------------------------------------------------


// Final returned struct to JS.
RenderedResult renderedResult() {
  return (RenderedResult) {
    .pixels = dynamicRenderedPixelArray(),
    .lines = dynamicRenderedLineArray()
  };
}

// Constructs wireframe with ready-to-fill arrays.
// TODO Make custom wireframe builder.
Wireframe wireframe() {
  return (Wireframe) {
    .vertices = dynamicPt3Array(),
    .edges = dynamicEdge3Array()
  };
}


//  ||====================================================
//  ||
//  || WIREFRAME MANAGEMENT METHODS ||||||||||||||||||||||
//  || 
//  ||====================================================


// Adds a vertex to a wireframe.
int addVertex(Wireframe* wireframePtr, Pt3 pt) {

  // Create vertex.
  addPt3(&wireframePtr->vertices, pt);

  // Return index of newest point (useful when building edges).
  return (wireframePtr->vertices.numElements-1);

}

// Removes vertex with given index from wireframe.
void rmVertex(Wireframe* wireframePtr, int index) {

  // Removes point from array.
  rmPt3(&wireframePtr->vertices, index);

  // Create a temp array.
  DynamicEdge3Array tempEdgeArr = dynamicEdge3Array();

  // Re-fill the temp array with recounted indexes.
  for (int i = 0; i < wireframePtr->edges.numElements; i++) {
    Edge3 tempEdge = wireframePtr->edges.data[i];

    if (tempEdge.startIndex == index || tempEdge.endIndex == index) {
      continue;
    }

    if (tempEdge.startIndex > index) {
      tempEdge.startIndex--;
    }

    if (tempEdge.endIndex > index) {
      tempEdge.endIndex--;
    }

    addEdge3(&tempEdgeArr, tempEdge);
    
  }

  // Free old array and replace with new one.

  free(wireframePtr->edges.data);      
  wireframePtr->edges = tempEdgeArr;

}

// Creates an edge between two vertexes.
void connectVertices(Wireframe* wireframePtr, int startIndex, int endIndex) {

    // Quick error check (should do this more consistently tbh):
    // -> both indices are in range
    // -> are not same vertex
    // TODO Check duplicate edges.
    if (!(startIndex >=  0 && startIndex < wireframePtr->vertices.numElements) ||
        !(endIndex >=  0 && endIndex < wireframePtr->vertices.numElements) ||
        (startIndex == endIndex)) {
        return;
    }

    // Adds an edge connected the two vertex indexes.
    addEdge3(&wireframePtr->edges, edge3(startIndex, endIndex));

}

// TODO write this func
// void removeEdge(Wireframe* wireframePtr, Edge3 edge) 

// Resets the wireframe.
void clearWireframe(Wireframe* wireframePtr) {
  clearPt3Array(&wireframePtr->vertices);
  clearEdge3Array(&wireframePtr->edges);
}


//  ||====================================================
//  ||
//  || CONVENIENCE FUNCTIONS |||||||||||||||||||||||||||||
//  || 
//  ||====================================================


// Convert 3D point to pixel on viewport.
// Psst i lowkey forgot if i use this function.. If i do then idk how..
Pixel ptToPx(Viewport viewport, Pt3 pt) {

    // Logic:
    // 1. Move it over so that it starts from (0, 0) in top left
    // 2. Then scale it down to fit viewport

    int x = (int)((pt.x + viewport.wrldWidth * 0.5f) *
                  (viewport.pxWidth / viewport.wrldWidth));

    int y = (int)((viewport.wrldHeight * 0.5f - pt.y) *
                  (viewport.pxHeight / viewport.wrldHeight));

    return pixel(x, y);
    
}



//  ||====================================================
//  ||
//  || RENDER FUNCTION |||||||||||||||||||||||||||||||||||
//  || 
//  ||====================================================


// The big fat important function of this project.
// Like the "take photo" button on a camera.
void render(Scene* scenePtr, RenderedResult* outputPtr) { 


  // CLEAR PREVIOUS DATA ||||||||||||||||||||||||||||||||
  // ====================================================


  clearRenderedPixelArray(&outputPtr->pixels); 
  clearRenderedLineArray(&outputPtr->lines);


  // SETUP PLANE + HELPFUL STUFF ||||||||||||||||||||||||
  // ====================================================


  // Create a plane at the origin facing Z+ (aka xy plane facing z+).
  // This works cuz we're not moving the camera - we're "moving" it with tranformations here in the render.
  // Note: can replace (0, 0, scenePtr-> etc) with a bunch of stuff referencing cam origin, thats unnecessary.
  // TODO is camOrigin unnecessary entirely with this new camspace design?  
  Plane viewportPlane = plane(vec3(0, 0, 1), pt3(0, 0, scenePtr->camera.viewportDistance));

  // This is an array of the pixel positions of all the vertexes.
  Pixel vertexPixels[scenePtr->wireframe->vertices.numElements];

  // This is a reference array to save whether a vertex is in front or behind the viewport.
  int vertexInFrontOfCamera[scenePtr->wireframe->vertices.numElements];

  // This is the reference array for points as they are after converted to camspace.
  Pt3 camSpacePts[scenePtr->wireframe->vertices.numElements];


  // RENDERING PART 1: VERTEXES |||||||||||||||||||||||||
  // ====================================================


  // Iterate through each vertex.
  for (int i = 0; i < scenePtr->wireframe->vertices.numElements; i++) {

    // Pull the vertex (point) we're working with.
    Pt3 pt = scenePtr->wireframe->vertices.data[i];


    // APPLY INVERSE TRANSFORMATIONS TO PT ||||||||||||||||
    // ----------------------------------------------------
    // *This I'm pretty sure is called converting a point 
    //  into camera space. 

    // Pull camera translation and change sign.
    Vec3 camTranslation = scenePtr->camera.transformation.translation;
    camTranslation.x *= -1;
    camTranslation.y *= -1;
    camTranslation.z *= -1;

    // Pull camera rotation and change sign.
    Vec3 camRotation = scenePtr->camera.transformation.rotation;
    camRotation.x *= -1;
    camRotation.y *= -1;
    camRotation.z *= -1;

    // HAVE TO APPLY APPLIED TRANSFORAMTIONS IN REVERSE ORDER (MOVE THEN ROTATE!!)
    // *So not just use the transform func I wrote with negative vals.
    
    // Move first (as my func first rotates).
    pt.x += camTranslation.x;
    pt.y += camTranslation.y;
    pt.z += camTranslation.z;

    // Convert to vector so rotation can happen.
    Vec3 temp = pt3ToVec3(pt);
    
    // rotateVec3(&temp, camRotation.x, camRotation.y, camRotation.z);
    // *Yeahh... cant use this func either cuz backwards rotation order :/

    // Setup rotation matrices (now with opposite sign operations).
    
  	Vec3 X_rotationMat3[3] = {
  								vec3(1, 0, 0),
                  vec3(0, cos(camRotation.x), sin(camRotation.x)),
  								vec3(0, -sin(camRotation.x), cos(camRotation.x))
  							};
      
  	Vec3 Y_rotationMat3[3] = {
  								vec3(cos(camRotation.y), 0, -sin(camRotation.y)),
                  vec3(0, 1, 0),
  								vec3(sin(camRotation.y), 0, cos(camRotation.y))
  							};

    // Apply rotations (again, in reverse order - did X then Y, now Y then X to undo).
    
    // YAW first (left/right; around y-axis).
    temp = multVec3Mat3(temp, Y_rotationMat3);

    // Then PITCH (up/down; around x-axis)
    temp = multVec3Mat3(temp, X_rotationMat3);

    // Convert back to point.
    pt = vec3ToPt3(temp);

    // Save it to camspace points for reference in edges.
    camSpacePts[i] = pt;
    

    // QUICK "PROJECTABLE" CHECK ||||||||||||||||||||||||||
    // ----------------------------------------------------


    // Check if the point is behind the cam origin.
    // Since the plane is flat at 

    // Why not behind viewport? Well because it would still work in 2D; the JS canvas allows out of bounds points.
    // So drawing a line between two points in front is still the same practically.

    // Here's a sketch, go figure what you can lmao :P
    
    /*

    [YZ PLANE VIEW]
    
        Y (pt)
       /  \
      |    \|
     /      \
    |       -\
    |       | \
    X (pt)  |  o (cam orig)
            | 
            - <-- viewport vertical border


    RESULT ON 2D 

            Y
           /
     -----/  <-- ooh line still drawn!
    |    / |
    |   X  | <-- viewport
    |      |
     ------
    */

    // but if its at or  behind the cam origin (which technically is always 0 since we're not moving the camera)
    // then its not really renderable, like saying "yo you see this [think of some object im too lazy to]" while
    // that object is really behind your head. Like no duh i dont see it. Same idea here, just we needa remember
    // those points for drawing edges (hence we saved it in camspace array)
    // + if its equal, then intersection becomes a line and thats lowkey not a point (cuz intersection func
    //   we use later returns a point and will break the program :(
    if (pt.z <= scenePtr->camera.camOrigin.z) {

      // Mark as not in front (0 --> false).
      vertexInFrontOfCamera[i] = 0;

      // Skip the vertex projection; we dont need to project it.
      // (ahem.. not directly at least.. stay tuned!)
      continue;
      
    }


    // PROCEED WITH PROJECTION ||||||||||||||||||||||||||||
    // ----------------------------------------------------


    // Create a line between camspaced point and the eye --> this is the direction vector.

    Vec3 dirvec = vec3(
      pt.x - scenePtr->camera.camOrigin.x,
      pt.y - scenePtr->camera.camOrigin.y,
      pt.z - scenePtr->camera.camOrigin.z
    );

    // Normalize it (cheeky lil optimization technique).
    normalizeVec3(&dirvec);

    // Compose the vector equation with dir vec and cam origin.
    Line3 line = line3(dirvec, scenePtr->camera.camOrigin);

    // Intersect this line with the viewport plane to get a point 
    Pt3 intersectionPoint = intersectionLinePlane(line, viewportPlane);

    
    // SAVE NECESSARY INFO ||||||||||||||||||||||||||||||||
    // ----------------------------------------------------

    
    // Note: This info will be used when dealing with edges in the next step. 

    // Save the projected pixel on the 2d canvas.
    Pixel projectedPixel = ptToPx(scenePtr->camera.viewport, intersectionPoint);

    // Add the pixel to the rendered ("output") struct. Mark it as in front of canvas for JS.
    addRenderedPixel(&outputPtr->pixels, renderedPixel(projectedPixel, 1));

    // Save the pixel (to connect edges later).
    vertexPixels[i] = projectedPixel;

    // Mark this vertex as being in front of the camera (ie renderable). 
    vertexInFrontOfCamera[i] = 1;
    
  }


  // RENDERING PART 2: EDGES ||||||||||||||||||||||||||||
  // ====================================================


  // Iterate through each edge.
  for (int i = 0; i < scenePtr->wireframe->edges.numElements; i++) {

    // Pull out the edge we're working with.
    Edge3 edge = scenePtr->wireframe->edges.data[i];

    // Ok listen up, there are really 3 conditions for edges and how they're drawn (or not drawn):
    // (Recall that an edge is a connection between 2 vertexes.)

    // Case 1: both vertexes exist outside of view.
    if (!vertexInFrontOfCamera[edge.startIndex] && !vertexInFrontOfCamera[edge.endIndex]) {

      // In this case, you shouldn't see any lines anyway. Skip and move to next edge. 
      // (like a line behind your head; ya probably shouldnt be able to see it.)
      continue;
      
    }

    
    // Case 2: both vertexes in view. 
    else if (vertexInFrontOfCamera[edge.startIndex] && vertexInFrontOfCamera[edge.endIndex]) {

      // Just create a line between the projected vertexes (their "pixel form") + add that to result.
      addRenderedLine(&outputPtr->lines, renderedLine(vertexPixels[edge.startIndex], vertexPixels[edge.endIndex]));

    }

    // Case 3: one vertex is in view, other is out.
    else {


        // DETERMINE CLIP POINT  ||||||||||||||||||||||||||||||
        // ----------------------------------------------------


        // Pull points we're working with (order doesnt really matter for the time being).
        Pt3 ptA = camSpacePts[edge.startIndex];
        Pt3 ptB = camSpacePts[edge.endIndex];

        // Now the strat is we create a 3d line between the two vertexes,
        // intersect THAT line with the viewport plane
        // and THEN we get the projection of that intersection 
        // and use that pixel + the pixel in view to draw a line on the canvas.

        // Get the dir vec between the two        
        Vec3 dirvec = vec3(
          ptA.x - ptB.x,
          ptA.y - ptB.y,
          ptA.z - ptB.z
        );

        // Normalize it (again, being mindful with a calm optimization technique).
        normalizeVec3(&dirvec);

        // Create 3D line with dir vec..
        Line3 line = line3(dirvec, ptA); // ptB also works; both will be on the line.

        // Get the point that intersects with viewport plane.
        Pt3 intersectionPoint = intersectionLinePlane(line, viewportPlane);

        // Get the projected pixel of that point.
        Pixel projPixel = ptToPx(scenePtr->camera.viewport, intersectionPoint);


        // CREATE LINE AND ADD ||||||||||||||||||||||||||||||||
        // ----------------------------------------------------


        // Create line between this projected pixel and whichever point is in view.

        RenderedLine renderLine;

        // If its the first point (the one at start index), use that one.
        if (vertexInFrontOfCamera[edge.startIndex]) {
          renderLine = renderedLine(projPixel, vertexPixels[edge.startIndex]);
        }
        // Otherwise use end index.
        else {
          renderLine = renderedLine(projPixel, vertexPixels[edge.endIndex]);
        }

        // Add this completed line to RenderedLines array.
        addRenderedLine(&outputPtr->lines, renderLine);
    }
  } 
}


//  ||====================================================
//  ||
//  || MODEL BUILDERS (MODELLER) FUNCTIONS |||||||||||||||
//  || 
//  || These funcs just create premade models for user
//  || to play around with.
//  || 
//  ||====================================================


void CUBE(Wireframe* model) {

    // CUBE IN FRONT OF CAMERA
    // camera at z = 0 looking +Z
    // cube spans z = 2 to z = 4
  
    int v0 = addVertex(model, pt3(-1, -1, 2));
    int v1 = addVertex(model, pt3(-1,  1, 2));
    int v2 = addVertex(model, pt3( 1,  1, 2));
    int v3 = addVertex(model, pt3( 1, -1, 2));

    int v4 = addVertex(model, pt3(-1, -1, 4));
    int v5 = addVertex(model, pt3(-1,  1, 4));
    int v6 = addVertex(model, pt3( 1,  1, 4));
    int v7 = addVertex(model, pt3( 1, -1, 4));


    // front face
    connectVertices(model, v0, v1);
    connectVertices(model, v1, v2);
    connectVertices(model, v2, v3);
    connectVertices(model, v3, v0);


    // back face
    connectVertices(model, v4, v5);
    connectVertices(model, v5, v6);
    connectVertices(model, v6, v7);
    connectVertices(model, v7, v4);


    // depth edges
    connectVertices(model, v0, v4);
    connectVertices(model, v1, v5);
    connectVertices(model, v2, v6);
    connectVertices(model, v3, v7);

}
