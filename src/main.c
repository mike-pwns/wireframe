/*

---



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
    // CUBE(&model);
    SYNTHSCAPE(&model);

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

    printf("did it");
}


//  ||----------------------------------------------------
//  ||
//  || JS APIs  ||||||||||||||||||||||||||||||||||||||||||
//  || 
//  || These functions are the ones that are ultimately
//  || called by the frontend. 
//  || 
//  ||----------------------------------------------------


// Initialize all program variables.
void initialize() {
    output = renderedResult();
    initializeSceneData();
}

// Returns WASM pointer to JS so it can parse the data of the render.
// Note: manual data parsing is super annoying/tedious, so AI did that.
RenderedResult* getRenderResult() {
    return &output;
}

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


  // gets movement to follow cam orientation
  Vec3 tempTranslation = vec3(x, y, z);
  rotateVec3(&tempTranslation,
             world.camera.transformation.rotation.x, 
             world.camera.transformation.rotation.y, 
             world.camera.transformation.rotation.z);

  world.camera.transformation.translation.x += tempTranslation.x;
  world.camera.transformation.translation.y += tempTranslation.y;
  world.camera.transformation.translation.z += tempTranslation.z;
  
}
