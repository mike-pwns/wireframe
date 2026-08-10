/*

  WHAT IS TEAMWORK REALLY WHEN YOU GET RIGHT DOWN TO IT?

  IS IT JUST ABOUT PROTECTING EACH OTHER AND HELPING EACH OTHER OUT?
  I GUESS MOST PEOPLE WOULD SAY SO, BUT THEY’RE JUST FOOLING THEMSELVES.

  I THINK TEAMWORK IS MORE THAN THAT IN THE END.
  IT’S ABOUT INDIVIDUALS TAKING INDIVIDUAL RISKS, IF YOU ASK ME.

  WE WORK TOGETHER BY WORKING SEPARATELY.

  YOU STAND UP TO RISK YOUR OWN LIFE.
  YOU DO WHAT YOU CAN, THE BEST THAT YOU CAN,
  THEN YOU TURN TO THE OTHERS AND EXPECT THE SAME FROM THEM.

  ---------------------------------------------------------------------

  "wireframe"
  @mike-pwns on GitHub

*/


#include "../include/linlib.h"
#include "../include/renderlib.h"
#include <math.h>
#include <stdio.h>


//  ||====================================================
//  ||
//  || PROGRAM VARIABLES |||||||||||||||||||||||||||||||||
//  || 
//  ||====================================================


RenderedResult output;
Wireframe model;
Scene world;


//  ||====================================================
//  ||
//  || METHODS |||||||||||||||||||||||||||||||||||||||||||
//  || 
//  ||====================================================


//  ||----------------------------------------------------
//  ||
//  || SCENE INITIALIZER  ||||||||||||||||||||||||||||||||
//  || 
//  || Initializes all necessary components such as 
//  || wireframe, viewport, camera, etc.  
//  || 
//  ||----------------------------------------------------


void initializeSceneData() {

    // Initialize wireframe (cube by default).
    
    model = wireframe();
    CUBE(&model);

    // Initialize camera.
    
    Camera cam = camera(
        pt3(0, 0, 0),                                 // WHERE THE CAM STARTS
        1,                                            // DIST (FOV)
        viewport(2, 2, 1024, 1024),                   // VIEWPORT DIMENSIONS
        transformation(vec3(0, 0, 0), vec3(0, 0, 0))  // DEFAULT TRANSFORMATION
    );

    // Compile into the scene/world.

    world = scene(
        &model,
        cam
    );

}


//  ||----------------------------------------------------
//  ||
//  || JS APIs  ||||||||||||||||||||||||||||||||||||||||||
//  || 
//  || These functions are the ones that are ultimately
//  || called by the frontend. 
//  || 
//  ||----------------------------------------------------


//  ||====================================================
//  || OUTPUT DATA ACCESS VIA POINTER ||||||||||||||||||||
//  ||====================================================


// Returns WASM pointer to JS so it can parse the data of the render.
// Note: manual data parsing is super annoying/tedious, so AI did that.
RenderedResult* getRenderResult() {
    return &output;
}


//  ||====================================================
//  || INITIALIZE PROGRAM ||||||||||||||||||||||||||||||||
//  ||====================================================


// Initialize all program variables.
void initialize() {
    output = renderedResult();
    initializeSceneData();
}


//  ||====================================================
//  || RENDER ("TAKE A PICTURE") |||||||||||||||||||||||||
//  ||====================================================


// Calls the render func from JS.
void renderScene() {
    render(&world, &output);
}

// Applies transformations to cam based on keyboard inputs on JS.
void transformCamera(float x, float y, float z, float radX, float radY, float radZ) { 
 
 
  // APPLY ROTATION.
 
 
  // Clamp pitch to [-PI/2, PI/2].
  if ((world.camera.transformation.rotation.x + radX) >= (PI/2)) {
      world.camera.transformation.rotation.x = PI/2;
  }
  else if ((world.camera.transformation.rotation.x + radX) <= (-PI/2)) {
      world.camera.transformation.rotation.x = -PI/2;
  }
  else {
    world.camera.transformation.rotation.x += radX;
  }
 
  // Apply YAW (rotation around the Y axis).
  world.camera.transformation.rotation.y += radY;
 
  // Apply Roll (rotation around the Z axis).
  // NOT USED FOR THIS PROJECT. (Only included for mathematical formality).
  world.camera.transformation.rotation.z += radZ;
 
 
  // APPLY TRANSLATION
 
 
  Vec3 tempTranslation = vec3(x, 0, z);
  rotateVec3(&tempTranslation,
             0,                                          // ignore pitch
             world.camera.transformation.rotation.y,     // yaw only
             world.camera.transformation.rotation.z);    // roll (unused anyway)
  
  world.camera.transformation.translation.x += tempTranslation.x;
  world.camera.transformation.translation.y += y;
  world.camera.transformation.translation.z += tempTranslation.z;
  
}


//  ||====================================================
//  || SWITCH MODELS |||||||||||||||||||||||||||||||||||||
//  ||====================================================


// (claude showed me i can define like this, super cool!)
#define MODEL_CUBE       0
#define MODEL_PYRAMID    1
#define MODEL_SPHERE     2
#define MODEL_OCTAHEDRON 3
#define MODEL_TORUS      4
#define MODEL_SYNTHSCAPE 5
#define MODEL_PENGUIN    6

// Switches model to the associated id provided.
void switchModel(int modelId) {

    // Clear the existing model.
    clearWireframe(&model);

    // Construct the new model.
    switch (modelId) {
        case MODEL_CUBE:       
          CUBE(&model);       
          break;
        case MODEL_PYRAMID:    
          PYRAMID(&model);    
          break;
        case MODEL_SPHERE:     
          SPHERE(&model);     
          break;
        case MODEL_OCTAHEDRON: 
          OCTAHEDRON(&model); 
          break;
        case MODEL_TORUS:      
          TORUS(&model);      
          break;
        case MODEL_SYNTHSCAPE: 
          SYNTHSCAPE(&model); 
          break;
        case MODEL_PENGUIN:    
          PENGUIN(&model);    
          break;
        default:               
          break;
    }

    // Reset camera transformation.
    world.camera.transformation = transformation(vec3(0, 0, 0), vec3(0, 0, 0));

}


//  ||====================================================
//  || CUSTOM MODEL BUILDER ||||||||||||||||||||||||||||||
//  ||==========================================[AI-GEN]==
 
 
// Adds a vertex to the active model. Returns its index.
int addCustomVertex(float x, float y, float z) {
    return addVertex(&model, pt3(x, y, z));
}
 
// Connects two vertices (by index) in the active model.
void connectCustomVertices(int startIndex, int endIndex) {
    connectVertices(&model, startIndex, endIndex);
}
 
// Clears just the wireframe - no camera reset. switchModel() clears AND
// resets the camera (used when you actually pick a new model from the
// gallery); this is the lighter version used every time the builder UI
// edits the custom model, so the camera stays put while you work.
void clearCustomModel() {
    clearWireframe(&model);
}

// Returns a pointer to the camera's LIVE transformation, so JS can
// read the real state instead of tracking its own pseudo-copy of the
// deltas it sends in. Memory layout (6 contiguous floats):
// [ tx, ty, tz, rx (pitch), ry (yaw), rz (roll) ]
Transformation* getCameraTransform() {
    return &world.camera.transformation;
}
 
