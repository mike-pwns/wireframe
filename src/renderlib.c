#include <stdio.h>
#include <stdlib.h>
#include "../include/renderlib.h"
#include "../include/linlib.h"
#include <math.h> // TODO  i should prolly just use the pi from this?

// ------------
// PRE SECTION
// ------------

// damnnnn youuuu and your stupidly simple fixed array ccccc!!!!!!!!!!! now i gotta figure out how to make dynamic array!!! no more fun and games like in python :(


DynamicPixelArray dynamicPixelArray() {
  return (DynamicPixelArray) {
    .data = malloc(sizeof(Pixel)),
    .numElements = 0,
    .capacity = 1
  };
}


void addPixel(DynamicPixelArray *arr, Pixel pixel) {
  // check if capacity,
  if (arr->numElements == arr->capacity) {
    // recreate, then copy all elements into there
    Pixel* temp = malloc((arr->capacity * 2) * sizeof(Pixel));

    for (int i = 0; i < arr->capacity; i++) {
      temp[i] = arr->data[i];
    }

    // free old data
    free(arr->data);

    // update capacity
    arr->capacity *= 2;

    // update data
    arr->data = temp;
    
  }

  // add point at latest and increment num elements
  arr->data[arr->numElements] = pixel;
  arr->numElements++;  
}

void clearPixelArray(DynamicPixelArray *arr) {
  free(arr->data);
  arr->data = malloc(sizeof(Pixel));
  arr->numElements = 0;
  arr->capacity = 1;
  
}











// EDGES




Edge3 edge3(int startIndex, int endIndex) {
  return (Edge3) {
    .startIndex = startIndex,
    .endIndex = endIndex
  };
}


// array







DynamicEdge3Array dynamicEdge3Array() {
  return (DynamicEdge3Array) {
    .data = malloc(sizeof(Edge3)),
    .numElements = 0,
    .capacity = 1
  };
}


void addEdge3(DynamicEdge3Array *arr, Edge3 edge3) {
  // check if capacity,
  if (arr->numElements == arr->capacity) {
    // recreate, then copy all elements into there
    Edge3* temp = malloc((arr->capacity * 2) * sizeof(Edge3));

    for (int i = 0; i < arr->capacity; i++) {
      temp[i] = arr->data[i];
    }

    // free old data
    free(arr->data);

    // update capacity
    arr->capacity *= 2;

    // update data
    arr->data = temp;
    
  }

  // add point at latest and increment num elements
  arr->data[arr->numElements] = edge3;
  arr->numElements++;  
}

void rmEdge3(DynamicEdge3Array *arr, int index) { 

  // just sanity check
  if (index < 0 || index >= arr->numElements) {
      return;
  }

  // is O(n)

  // recreate the array
  Edge3* temp = malloc(arr->capacity * sizeof(Edge3));

  // flag for removed; will have to offset copy index
  int removed = 0; // will set to 1

  // iterate all pts
  for (int i = 0; i < arr->numElements; i++) {      

    // if its the index, dont copy anything, just set rmvd true
    if (i == index) {
      removed = 1;
    }

    // otherwise copy based on whether index was passed or not
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






// point array (for scene)
// logic, doubles every time limit is reached. default size one



DynamicPt3Array dynamicPt3Array() {
  return (DynamicPt3Array) {
    .data = malloc(sizeof(Pt3)),
    .numElements = 0,
    .capacity = 1
  };
}


void addPt3(DynamicPt3Array *arr, Pt3 pt) {
  // check if capacity,
  if (arr->numElements == arr->capacity) {
    // recreate, then copy all elements into there
    Pt3* temp = malloc((arr->capacity * 2) * sizeof(Pt3));

    for (int i = 0; i < arr->capacity; i++) {
      temp[i] = arr->data[i];
    }

    // free old data
    free(arr->data);

    // update capacity
    arr->capacity *= 2;

    // update data
    arr->data = temp;
    
  }

  // add point at latest and increment num elements
  arr->data[arr->numElements] = pt;
  arr->numElements++;  
}

void rmPt3(DynamicPt3Array *arr, int index) { 

  // just sanity check
  if (index < 0 || index >= arr->numElements) {
      return;
  }

  // is O(n)

  // recreate the array
  Pt3* temp = malloc(arr->capacity * sizeof(Pt3));

  // flag for removed; will have to offset copy index
  int removed = 0; // will set to 1

  // iterate all pts
  for (int i = 0; i < arr->numElements; i++) {      

    // if its the index, dont copy anything, just set rmvd true
    if (i == index) {
      removed = 1;
    }

    // otherwise copy based on whether index was passed or not
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

void clearPt3Array(DynamicPt3Array *arr) {
  free(arr->data);
  arr->data = malloc(sizeof(Pt3));
  arr->numElements = 0;
  arr->capacity = 1;
  
}







Wireframe wireframe() {
  return (Wireframe) {
    .vertices = dynamicPt3Array(),
    .edges = dynamicEdge3Array()
  };
}

// returns the index of the vertex added (good for edge building)
int addVertex(Wireframe* wireframePtr, Pt3 pt) {
  addPt3(&wireframePtr->vertices, pt);
  return (wireframePtr->vertices.numElements-1);
}


void rmVertex(Wireframe* wireframePtr, int index) {
  rmPt3(&wireframePtr->vertices, index);

  // remove any edges with said vertex
  DynamicEdge3Array tempEdgeArr = dynamicEdge3Array();

  for (int i = 0; i < wireframePtr->edges.numElements; i++) {
    Edge3 tempEdge = wireframePtr->edges.data[i];

    if (tempEdge.startIndex == index || tempEdge.endIndex == index) {
      continue;
    }

    // set all vertexes with index higher 1 down
    if (tempEdge.startIndex > index) {
      tempEdge.startIndex--;
    }

    if (tempEdge.endIndex > index) {
      tempEdge.endIndex--;
    }

    // add it to the new arr
    addEdge3(&tempEdgeArr, tempEdge);
    
  }


  free(wireframePtr->edges.data);      
  wireframePtr->edges = tempEdgeArr;

}


void connectVertices(Wireframe* wireframePtr, int startIndex, int endIndex) {

    // sanity check; start & end indexes are in range, and its not the same vertex
    if (!(startIndex >=  0 && startIndex < wireframePtr->vertices.numElements) ||
        !(endIndex >=  0 && endIndex < wireframePtr->vertices.numElements) ||
        (startIndex == endIndex)) {
        return;
    }
    // for later; duplicate edges?
  

    addEdge3(&wireframePtr->edges, edge3(startIndex, endIndex));
}


// void removeEdge(Wireframe* wireframePtr, Edge3 edge) 

void clearWireframe(Wireframe* wireframePtr) {
  clearPt3Array(&wireframePtr->vertices);
  clearEdge3Array(&wireframePtr->edges);
}









// ------------
// PRE SECTION
// ------------



// --------------------
// CanvasPixel
// --------------------

Pixel pixel(int x, int y) {
    return (Pixel){
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

Scene scene(Wireframe* wireframe, Camera camera) {
    return (Scene){
        .wireframe = wireframe,
        .camera = camera
    };
}




Pixel ptToPx(Viewport viewport, Pt3 pt) {
    // move it over so that it starts from (0, 0) in top left
    // then scale it down to fit viewport

    int x = (int)((pt.x + viewport.wrldWidth * 0.5f) *
                  (viewport.pxWidth / viewport.wrldWidth));

    int y = (int)((viewport.wrldHeight * 0.5f - pt.y) *
                  (viewport.pxHeight / viewport.wrldHeight));

    return pixel(x, y);
}









// RENDERED STRUCTS (final outputtable for js)
RenderedPixel renderedPixel(Pixel pixel, int isInFrontOfCamera) {

  return (RenderedPixel) {
    .pixel = pixel,
    .isInFrontOfCamera = isInFrontOfCamera
  };

}


RenderedLine renderedLine(Pixel startPixel, Pixel endPixel) {

  return (RenderedLine) {
    .startPixel = startPixel,
    .endPixel = endPixel
  };

}



// -------------------------
// Dynamic RenderedPixel Array
// -------------------------


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



// -------------------------
// Dynamic RenderedLine Array
// -------------------------


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



// -------------------------
// Render Result
// -------------------------


RenderedResult renderedResult() {

  return (RenderedResult) {
    .pixels = dynamicRenderedPixelArray(),
    .lines = dynamicRenderedLineArray()
  };

}










// renders everything as it is
void render(Scene* scenePtr, RenderedResult* outputPtr) { 

  // clear all previous stuff
  clearRenderedPixelArray(&outputPtr->pixels); 
  clearRenderedLineArray(&outputPtr->lines);

  // TESTING!!!
  // add(canvasPixelArrPtr, canvasPixel(1, 2));
  // printCanvasPixelArray(*canvasPixelArrPtr);


  // ACTUAL STUFF

  
  // get plane (normal is z axis, known point is (0, 0, viewportDistance))

  Plane viewportPlane = plane(vec3(0, 0, 1), pt3(scenePtr->camera.camOrigin.x, scenePtr->camera.camOrigin.y, scenePtr->camera.camOrigin.z + scenePtr->camera.viewportDistance));
                        

  Pixel vertexPixels[scenePtr->wireframe->vertices.numElements];
  int vertexInFrontOfCamera[scenePtr->wireframe->vertices.numElements];

  // Perform calcs and add to canvas

  // ------------------
  // STEP 1: VERTEXES

  for (int i = 0; i < scenePtr->wireframe->vertices.numElements; i++) {
  
    Pt3 pt = scenePtr->wireframe->vertices.data[i];


    // check if the point is behind the camera
    if (pt.z <= scenePtr->camera.camOrigin.z) {

      // if it is 
      vertexInFrontOfCamera[i] = 0;
      continue;
    }

    // create line (vector) --> this is the direction vector.

    Vec3 dirvec = vec3(
      pt.x - scenePtr->camera.camOrigin.x,
      pt.y - scenePtr->camera.camOrigin.y,
      pt.z - scenePtr->camera.camOrigin.z
    );

    normalizeVec3(&dirvec);

    Line3 line = line3(dirvec, scenePtr->camera.camOrigin);

    Pt3 intersectionPoint = intersectionLinePlane(line, viewportPlane);

    // convert to px and add


    // =========> BAND AID
    intersectionPoint.x -= scenePtr->camera.camOrigin.x;
    intersectionPoint.y -= scenePtr->camera.camOrigin.y;
    // =========> BAND AID

    
    Pixel projectedPixel = ptToPx(scenePtr->camera.viewport, intersectionPoint);
    addRenderedPixel(&outputPtr->pixels, renderedPixel(projectedPixel, 1));
    vertexPixels[i] = projectedPixel;
    vertexInFrontOfCamera[i] = 1;
    
  }

  // ----------------
  // STEP 2: construct edges
  for (int i = 0; i < scenePtr->wireframe->edges.numElements; i++) {
    Edge3 edge = scenePtr->wireframe->edges.data[i];

    // if both exist outside of view, dont do anythin
    if (!vertexInFrontOfCamera[edge.startIndex] && !vertexInFrontOfCamera[edge.endIndex]) {
      continue;
    }
    // if both in view, keep the us(ual)
    else if (vertexInFrontOfCamera[edge.startIndex] && vertexInFrontOfCamera[edge.endIndex]) {
      addRenderedLine(&outputPtr->lines, renderedLine(vertexPixels[edge.startIndex], vertexPixels[edge.endIndex]));
    }

    // one is in, one is out
    else {

        Pt3 ptA = scenePtr->wireframe->vertices.data[edge.startIndex];
        Pt3 ptB = scenePtr->wireframe->vertices.data[edge.endIndex];
    
        // create line
        Vec3 dirvec = vec3(
          ptA.x - ptB.x,
          ptA.y - ptB.y,
          ptA.z - ptB.z
        );

        Line3 line = line3(dirvec, ptA); // or b either work

        // intersect with plane
        Pt3 intersectionPoint = intersectionLinePlane(line, viewportPlane);

        // generate projected point
        // =========> BAND AID
        intersectionPoint.x -= scenePtr->camera.camOrigin.x;
        intersectionPoint.y -= scenePtr->camera.camOrigin.y;
        // =========> BAND AID

        Pixel projPixel = ptToPx(scenePtr->camera.viewport, intersectionPoint);
        
        // create line and add to list

        // if it is the first point in view, go from this to clipped

        RenderedLine renderLine;
        
        if (vertexInFrontOfCamera[edge.startIndex]) {
          renderLine = renderedLine(projPixel, vertexPixels[edge.startIndex]);
        }
        // otherwise start from end index
        else {
          renderLine = renderedLine(projPixel, vertexPixels[edge.endIndex]);
        }

        // add this to render lines
        addRenderedLine(&outputPtr->lines, renderLine);
    }
    
  
  } 
  

}



















void printDynamicPixelArray(DynamicPixelArray arr) {

    printf("CanvasPixelArray {\n");
    printf("  # elements: %d\n", arr.numElements);
    printf("  pixels:\n");

    for (int i = 0; i < arr.numElements; i++) {
        printf("    [%d] (%d, %d)\n",
               i,
               arr.data[i].x,
               arr.data[i].y);
    }

    printf("}\n");
}

// void printScene(Scene scene) {
// 
//     printf("Scene {\n");
// 
//     printf("  numPts: %d\n", scene.numPts);
// 
//     printf("  points:\n");
//     for (int i = 0; i < scene.numPts; i++) {
//         printf("    [%d] ", i);
//         printPt3(scene.points[i]);
//     }
// 
//     printf("  camera:\n");
// 
//     printf("    origin: ");
//     printPt3(scene.camera.camOrigin);
// 
//     printf("    viewportDistance: %f\n",
//            scene.camera.viewportDistance);
// 
//     printf("    viewport:\n");
//     printf("      worldWidth : %f\n",
//            scene.camera.viewport.wrldWidth);
//     printf("      worldHeight: %f\n",
//            scene.camera.viewport.wrldHeight);
//     printf("      pixelWidth : %d\n",
//            scene.camera.viewport.pxWidth);
//     printf("      pixelHeight: %d\n",
//            scene.camera.viewport.pxHeight);
// 
//     printf("}\n");
// }
  


