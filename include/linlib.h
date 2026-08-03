#ifndef LINLIB_H
#define LINLIB_H


//  ||====================================================
//  ||
//  || CONSTANTS |||||||||||||||||||||||||||||||||||||||||
//  || 
//  ||====================================================


// Mathematical constant PI.
#define PI 3.14159265358979323846


//  ||====================================================
//  ||
//  || STRUCTS |||||||||||||||||||||||||||||||||||||||||||
//  || 
//  ||====================================================


//  ||----------------------------------------------------
//  ||
//  || VECTOR STRUCTS  |||||||||||||||||||||||||||||||||||
//  || 
//  || Structs for vectors in 2D and 3D.
//  || 
//  ||----------------------------------------------------


// 2D vector.
typedef struct {

	float x;
	float y;
	
} Vec2;
Vec2 vec2(float x, float y);


// 3D vector.
typedef struct {

	float x;
	float y;
	float z;
	
} Vec3;
Vec3 vec3(float x, float y, float z);


//  ||----------------------------------------------------
//  ||
//  || POINT STRUCTS  |||||||||||||||||||||||||||||||||||
//  || 
//  || Structs for points (for this proj only 3D). 
//  || 
//  ||----------------------------------------------------


// Point in 3D.
typedef struct {

	float x;
	float y;
	float z;
	
} Pt3;
Pt3 pt3(float x, float y, float z);

// Dynamic array for Pt3.
typedef struct {

  Pt3* data;
  int numElements;
  int capacity;

} DynamicPt3Array;
DynamicPt3Array dynamicPt3Array();
void addPt3(DynamicPt3Array *arr, Pt3 pt);
void rmPt3(DynamicPt3Array *arr, int index);
void clearPt3Array(DynamicPt3Array *arr);


//  ||----------------------------------------------------
//  ||
//  || "LINEAR STRUCTURES" STRUCTS  ||||||||||||||||||||||
//  || 
//  || Lines and Planes (may leave out 2d; dont need em
//  || for this project) 
//  || 
//  ||----------------------------------------------------


// Line in 3D space.
// Format is from vector equation: PT + DIR_VEC(t).
typedef struct {

  Vec3 dirVec;
  Pt3 pt;
  
} Line3;
Line3 line3(Vec3 dirVec, Pt3 pt);


// Plane in 3D space.
// Format is from cartesian equation: Ax + By + Cz + d = 0.
typedef struct {

  Vec3 normVec;
  Pt3 pt;
  
} Plane; 
Plane plane(Vec3 normVec, Pt3 pt);

// 3D Transformation. 
// (Didn't specify in struct that it was 3d, sorry!)
typedef struct {

  Vec3 translation;
  Vec3 rotation;
  
} Transformation;
Transformation transformation(Vec3 translation, Vec3 rotation);
void transformPt(Transformation transformation, Pt3* pt);


//  ||====================================================
//  ||
//  || METHODS |||||||||||||||||||||||||||||||||||||||||||
//  || 
//  ||====================================================


//  ||----------------------------------------------------
//  ||
//  || VECTOR OPERATIONS  ||||||||||||||||||||||||||||||||
//  || 
//  || Vector add, mult. 
//  || 
//  ||----------------------------------------------------


//  ||====================================================
//  || ADDITION ||||||||||||||||||||||||||||||||||||||||||
//  ||====================================================


// Add 2 2D vectors.
Vec2 addVec2(Vec2 vecA,  Vec2 vecB);

// Add 2 3D vectors.
Vec3 addVec3(Vec3 vecA, Vec3 vecB);


//  ||====================================================
//  || MULTIPLICATION ||||||||||||||||||||||||||||||||||||
//  ||====================================================


// Dot product of 2 2D vectors.
float dotVec2(Vec2 vecA, Vec2 vecB);

// Dot product of 2 3D vectors.
float dotVec3(Vec3 vecA, Vec3 vecB);

// Cross product of 2 3D vectors.
Vec3 crossVec3(Vec3 vecA, Vec3 vecB);


//  ||====================================================
//  || ROTATION ||||||||||||||||||||||||||||||||||||||||||
//  ||====================================================


// Rotates a given 2D vector by given radians.
void rotateVec2(Vec2 *vecPtr, float radians);
void rotateVec3(Vec3 *vecPtr, float radX, float radY, float radZ);


//  ||----------------------------------------------------
//  ||
//  || MATRIX OPERATIONS  ||||||||||||||||||||||||||||||||
//  || 
//  || Determinants, multiplication. 
//  || 
//  ||----------------------------------------------------


//  ||====================================================
//  || DETERMINANT |||||||||||||||||||||||||||||||||||||||
//  ||====================================================


// Determinant of 2D matrix.
float detMat2(Vec2 mat2[]);

// Determinant of 3D matrix.
float detMat3(Vec3 mat3[]);


//  ||====================================================
//  || MULTIPLICATION ||||||||||||||||||||||||||||||||||||
//  ||====================================================


Vec3 multVec3Mat3(Vec3 vec3, Vec3 mat3[]);

// matmult (real ones know about this one!)
// Didnt implement yet.


//  ||----------------------------------------------------
//  ||
//  || INTERSECTIONS N STUFF |||||||||||||||||||||||||||||
//  || 
//  || Intersections of relevant things.
//  || 
//  ||----------------------------------------------------


// Intersects a given line with a given plane and returns point.
Pt3 intersectionLinePlane(Line3 line, Plane plane);

// technically should write more for the "complete linlib collection" but honestly behh meh im not doin allat!


//  ||----------------------------------------------------
//  ||
//  || CONVENIENT STUFF ||||||||||||||||||||||||||||||||||
//  || 
//  || Casting pts and vectors cuz i guess thats what we
//  || do now??
//  || 
//  ||----------------------------------------------------


// Magnitude of a 3D vector.
float magVec3(Vec3 vec3);

// Reduces / Converts 3D vector to unit vector.
void normalizeVec3(Vec3* vec3);

// Converts Pt3 struct to Vec3 struct.
Vec3 pt3ToVec3(Pt3 pt3);

// Converts Vec3 struct to Pt3 struct.
Pt3 vec3ToPt3(Vec3 vec3);


//  ||----------------------------------------------------
//  ||
//  || PRINT FORMATTING  |||||||||||||||||||||||||||||||||
//  || 
//  || Convenient printing functions for debugging.
//  || 
//  ||----------------------------------------------------


//  ||====================================================
//  || VECTORS |||||||||||||||||||||||||||||||||||||||||||
//  ||====================================================


// Prints formatted 2D vector.
void printVec2(Vec2 vec);

// Prints formatted 3D vector.
void printVec3(Vec3 vec);


//  ||====================================================
//  || MATRICES ||||||||||||||||||||||||||||||||||||||||||
//  ||====================================================


// Prints formatted 2D matrix.
void printMat2(Vec2 mat2[]);

// Prints formatted 3D matrix.
void printMat3(Vec3 mat3[]);

// Prints formatted 3D point.
void printPt3(Pt3 pt);

#endif
