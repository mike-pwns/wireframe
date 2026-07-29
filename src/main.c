#include <stdio.h>

// remove the ../include on official compilation, instead do -I include/
#include "../include/linlib.h"
#include "../include/renderlib.h"


Wireframe model;
RenderedResult output;
Scene world;


void initializeSceneData() {

    model = wireframe();

    // CUBE IN FRONT OF CAMERA
    // camera at z = 0 looking +Z
    // cube spans z = 2 to z = 4

    int v0 = addVertex(&model, pt3(-1, -1, 2));
    int v1 = addVertex(&model, pt3(-1,  1, 2));
    int v2 = addVertex(&model, pt3( 1,  1, 2));
    int v3 = addVertex(&model, pt3( 1, -1, 2));

    int v4 = addVertex(&model, pt3(-1, -1, 4));
    int v5 = addVertex(&model, pt3(-1,  1, 4));
    int v6 = addVertex(&model, pt3( 1,  1, 4));
    int v7 = addVertex(&model, pt3( 1, -1, 4));


    // front face
    connectVertices(&model, v0, v1);
    connectVertices(&model, v1, v2);
    connectVertices(&model, v2, v3);
    connectVertices(&model, v3, v0);


    // back face
    connectVertices(&model, v4, v5);
    connectVertices(&model, v5, v6);
    connectVertices(&model, v6, v7);
    connectVertices(&model, v7, v4);


    // depth edges
    connectVertices(&model, v0, v4);
    connectVertices(&model, v1, v5);
    connectVertices(&model, v2, v6);
    connectVertices(&model, v3, v7);



    // camera

    // issue was that viewport plane didnt follow the camera origin
    Pt3 origin = pt3(0, 0, 0);

    Viewport vp = viewport(2, 2, 1024, 1024);

    Transformation trans = transformation(vec3(0, 0, 0), vec3(0, 0, 0));

    Camera cam = camera(
        origin,
        1,
        vp,
        trans
    );

    world = scene(
        &model,
        cam
    );
}



// JS API

RenderedResult* getRenderResult() {
    return &output;
}



// render the scene
void renderScene() {
    render(&world, &output);
}




void transformCamera(float x, float y, float z, float radX, float radY, float radZ) {
  world.camera.transformation.translation.x += x;
  world.camera.transformation.translation.y += y; 
  world.camera.transformation.translation.z += z; 
  world.camera.transformation.rotation.x += radX;
  world.camera.transformation.rotation.y += radY;
  world.camera.transformation.rotation.z += radZ;
  
}


// init

void initialize() {

    output = renderedResult();
    initializeSceneData();

}
