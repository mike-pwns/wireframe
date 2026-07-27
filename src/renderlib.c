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
  arr->data = malloc(sizeof(Pt3));
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
    .data = malloc(sizeof(Pt3)),
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

Scene scene(DynamicPt3Array *pt3Arr, Camera camera) {
    return (Scene){
        .pt3Arr = pt3Arr,
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






















// renders everything as it is
void  render(DynamicPixelArray* arr, Scene* scenePtr) { 

  // clear all previous pixels
  clearPixelArray(arr); 

  // TESTING!!!
  // add(canvasPixelArrPtr, canvasPixel(1, 2));
  // printCanvasPixelArray(*canvasPixelArrPtr);


  // ACTUAL STUFF
  
  // get plane (normal is z axis, known point is (0, 0, viewportDistance))

  Plane viewportPlane = plane(vec3(0, 0, 1), pt3(0, 0, scenePtr->camera.viewportDistance));

  // Perform calcs and add to canvas

  for (int i = 0; i < scenePtr->pt3Arr->numElements; i++) {
  
    Pt3 pt = scenePtr->pt3Arr->data[i];

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

    // REMOVED WHEN DEALING WITH EDGES:
    // - what if we wanna draw edges to outside of the screen?
    // we still gonna need points for that! so doesnt matter if its in here or not.
    
//   if (
//       !(
// 
//         // check x range
//         (scenePtr->camera.camOrigin.x - 0.5f * scenePtr->camera.viewport.wrldWidth) <= intersectionPoint.x &&
//         intersectionPoint.x <= (scenePtr->camera.camOrigin.x + 0.5f * scenePtr->camera.viewport.wrldWidth) &&
// 
// 
//         // check y range
//         scenePtr->camera.camOrigin.y - 0.5f * scenePtr->camera.viewport.wrldHeight <= intersectionPoint.y &&
//         intersectionPoint.y <= scenePtr->camera.camOrigin.y + 0.5f * scenePtr->camera.viewport.wrldHeight)
//   ) {
//       continue;
//   }

    // convert to px and add
    addPixel(arr, ptToPx(scenePtr->camera.viewport, intersectionPoint));
    

    
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
  


