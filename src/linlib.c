// Bienvenue a ma bibliotheque d'algebra liniaire!!


#include <stdio.h>
#include "../include/linlib.h"
#include <math.h> 
#include <stdlib.h>


//  ||====================================================
//  ||
//  || "CONSTRUCTORS" AND DYNAMIC ARRAYS |||||||||||||||||
//  || 
//  ||====================================================


//  ||----------------------------------------------------
//  ||
//  || STRUCT CONSTRUCTORS  ||||||||||||||||||||||||||||||
//  || 
//  || Standard constructors idk what else to say. 
//  || 
//  ||----------------------------------------------------


// 2D vector.
Vec2 vec2(float x, float y) {
  return (Vec2) {
    .x = x,
    .y = y
  };
}

// 3D vector.
Vec3 vec3(float x, float y, float z) {
  return (Vec3) {
    .x = x,
    .y = y,
    .z = z
  };
}

// 3D point.
Pt3 pt3(float x, float y, float z) {
  return (Pt3) {
    .x = x,
    .y = y,
    .z = z
  };
}

// Line in 3D.
Line3 line3(Vec3 dirVec, Pt3 pt) {
  return (Line3) {
    .dirVec = dirVec,
    .pt = pt
  };
}

// Plane ("in 3D").
Plane plane(Vec3 normVec, Pt3 pt) {
  return (Plane) {
    .normVec = normVec,
    .pt = pt
  };
}

// Transformation.
Transformation transformation(Vec3 translation, Vec3 rotation) {
  return (Transformation) {
    .translation = translation,
    .rotation = rotation
  };
}


//  ||----------------------------------------------------
//  ||
//  || DYNAMIC ARRAYS & FRIENDS (METHODS)  |||||||||||||||
//  || 
//  || Just dynamic arrays for necessary objects and 
//  || their respective add/remove/etc implementations. 
//  || 
//  ||----------------------------------------------------


// Constructor.
DynamicPt3Array dynamicPt3Array() {
  return (DynamicPt3Array) {
    .data = malloc(sizeof(Pt3)),
    .numElements = 0,
    .capacity = 1
  };
}


// Add element.
void addPt3(DynamicPt3Array *arr, Pt3 pt) {

  // Check if capacity reached.
  if (arr->numElements == arr->capacity) {
  
    // If reached, recreate the array with double the capacity.
    Pt3* temp = malloc((arr->capacity * 2) * sizeof(Pt3));

    // Then copy all elements into the new one.
    for (int i = 0; i < arr->capacity; i++) {
      temp[i] = arr->data[i];
    }

    // free old data.
    free(arr->data);

    // update capacity var.
    arr->capacity *= 2;

    // update data.
    arr->data = temp;
    
  }

  // Add point at latest and increment num elements.
  arr->data[arr->numElements] = pt;
  arr->numElements++;  
  
}

// Remove element.
void rmPt3(DynamicPt3Array *arr, int index) { 

  // Just check (should do this more often).
  if (index < 0 || index >= arr->numElements) {
      return;
  }

  // (Pt3 DynamicArray) Recreate array.
  Pt3* temp = malloc(arr->capacity * sizeof(Pt3));

  // Flag for removed; will have to offset copy index.
  int removed = 0; // will set to 1.

  // Iterate all pts
  for (int i = 0; i < arr->numElements; i++) {      

    // If its the index, dont copy anything, just set rmvd true.
    if (i == index) {
      removed = 1;
    }

    // Otherwise copy based on whether index was passed or not.
    else {

      // Yeah sure can do else if but whatevs man.
    
      if (removed) {
        temp[i-1] = arr->data[i];
      }
      else {
        temp[i] = arr->data [i];
      }
    }
  }

  // Free old data.
  free(arr->data);

  // Set new data, decrement num elements.
  arr->data = temp;
  arr->numElements--;  
  
}

// (Pt3 DynamicArray) Clears the array entirely, "blank slate".
void clearPt3Array(DynamicPt3Array *arr) {

  // Free old array.
  free(arr->data);

  // Allocate mem and create new ptr.
  arr->data = malloc(sizeof(Pt3));

  // Set default vars.
  arr->numElements = 0;
  arr->capacity = 1;
  
}


//  ||====================================================
//  ||
//  || VECTOR ARITHMETIC |||||||||||||||||||||||||||||||||
//  || 
//  ||====================================================


//  ||====================================================
//  || ADDITION  |||||||||||||||||||||||||||||||||||||||||
//  ||====================================================


// Returns the 2D resultant vector.
Vec2 addVec2(Vec2 vecA, Vec2 vecB) {

	Vec2 result;

	result.x = (vecA.x + vecB.x);
	result.y = (vecA.y + vecB.y);

	return result;
	
}

// Returns the 3D resultant vector.
Vec3 addVec3(Vec3 vecA, Vec3 vecB) {

	Vec3 result;
	
	result.x = (vecA.x + vecB.x);
	result.y = (vecA.y + vecB.y);
	result.z = (vecA.z + vecB.z);

	return result;
		
}


//  ||====================================================
//  || MULITPLICATION  |||||||||||||||||||||||||||||||||||
//  ||====================================================


// Returns dot product of 2 2D vectors.
float dotVec2(Vec2 vecA, Vec2 vecB) {

	float result = (vecA.x * vecB.x) + (vecA.y * vecB.y);

	return result;

}

// Returns dot product of 2 3D vectors.
float dotVec3(Vec3 vecA, Vec3 vecB) {

	float result = (vecA.x * vecB.x) + (vecA.y * vecB.y) + (vecA.z * vecB.z);

	return result;	
	
}

// Returns 3D vector; result of cross product.
Vec3 crossVec3(Vec3 vecA, Vec3 vecB) {

	Vec3 result;

	// algorithmically the same as laplace but 
	// dif i dont fully understand yet but maybe i will.

	// i-hat

	Vec2 subMatI[2] = {
              vec2(vecA.y, vecB.y),
              vec2(vecA.z, vecB.z)
            };

	result.x = (1) * detMat2(subMatI); // (+)

	// j-hat
	
	Vec2 subMatJ[2] = {
  	          vec2(vecA.x, vecB.x),
  	          vec2(vecA.z, vecB.z)
	          };


	result.y = (-1) * detMat2(subMatJ); // (-)

	// k-hat

	Vec2 subMatK[2] = {
  	          vec2(vecA.x, vecB.x),
  	          vec2(vecA.y, vecB.y)
	          };

	
	result.z = (1) * detMat2(subMatK); // (+)

	// return result
	
	return result;

}


//  ||====================================================
//  ||
//  || MATRIX MATH |||||||||||||||||||||||||||||||||||||||
//  || 
//  ||====================================================


//  ||====================================================
//  || DETERMINANTS ||||||||||||||||||||||||||||||||||||||
//  ||====================================================


// Returns determinant of 2D matrix.
float detMat2(Vec2 mat2[]) {

	Vec2 vecA = mat2[0]; // column vec
	Vec2 vecB = mat2[1]; // column vec

	float result = (vecA.x * vecB.y) - (vecB.x * vecA.y);

	return result;
	
}

// Returns determinant of 3D matrix.
float detMat3(Vec3 mat3[]) {

	Vec3 vecA = mat3[0];
	Vec3 vecB = mat3[1];
	Vec3 vecC = mat3[2];

	// perform cofactor (laplace) expansion
	// this is done like id do it on paper cuz im learning this for first time
	// yea can be optimized but screw that this is for fun

	// *note: not doing the whole cofactor thing for a 3x3, i alr know its (+ - +)


	// TERM 1 (of 3)


	float elementA = vecA.x;

	Vec2 subMatA[2] = {
	            vec2(vecB.y, vecB.z),
	            vec2(vecC.y, vecC.z)
					  };						

	float minorA = detMat2(subMatA);

	float termA = (1 * elementA * minorA);


	// TERM 2 (of 3)	


	float elementB = vecB.x;

	Vec2 subMatB[2] = {
              vec2(vecA.y, vecA.z),
              vec2(vecC.y,vecC.z)
            };						

	float minorB = detMat2(subMatB);

	float termB = (-1 * elementB * minorB); 
	

	// TERM 3 (of 3)


	float elementC = vecC.x;

	Vec2 subMatC[2] = {
              vec2(vecA.y, vecA.z),
              vec2(vecB.y, vecB.z)
					  };

	float minorC = detMat2(subMatC);

	float termC = (1 * elementC * minorC);


	// Put together and return.
	
	float result = termA + termB + termC;

	return result;
	
}


//  ||====================================================
//  || MULITPLICATION  |||||||||||||||||||||||||||||||||||
//  ||====================================================


// Returns the result of multiplying a vec2 by a mat2. 
// AKA Applying a tranformation on a 2d vector.
Vec2 multVec2Mat2(Vec2 vec2, Vec2 mat2[]) {

	Vec2 result;

	// Split the matrix into its 2 column vectors.
	Vec2 matVecI = mat2[0];
	Vec2 matVecJ = mat2[1];	

	/*

	Logic:

	All matrix multiplication is, is APPLYING the transformation.

	So pretty much setting the basis vectors of a matrix (i and j (and k for 3d)) to these new given vectors.

	To do this we rewrite the og vec as ix + jy, then replace i and j with the 2 column vectors.

	simplify and bim bam boom you get whatever is below. 

	*/ 
	
	result.x = (matVecI.x * vec2.x) + (matVecJ.x * vec2.y);
	result.y = (matVecI.y * vec2.x) + (matVecJ.y * vec2.y);

	return result;
	
}

// Returns the result of multiplying a vec2 by a mat3. 
// AKA Applying a tranformation on a 3d vector.
Vec3 multVec3Mat3(Vec3 vec3, Vec3 mat3[]) {

  Vec3 result;

  // Split up matrix into column vectors.
  Vec3 matVecI = mat3[0];
  Vec3 matVecJ = mat3[1];
  Vec3 matVecK = mat3[2];
  
  /*

  (Ignore, just space to figure it out for myself.)
  
  | i j k | |a|
  | l m n | |b|
  | o p q | |c|

  |i|     |j|     |k|
  |l| a + |m| b + |n| c
  |o|     |p|     |q|

  x = ia + jb + kc ; x = matVecI.x*vec.x + matVecJ.x*vec.y + matVecK.z*
  y = la + mb + nc; etc
  z = 0a + pb + qc; etc
  
  */

  result.x = (matVecI.x * vec3.x) + (matVecJ.x * vec3.y) + (matVecK.x * vec3.z);
  result.y = (matVecI.y * vec3.x) + (matVecJ.y * vec3.y) + (matVecK.y * vec3.z);
  result.z = (matVecI.z * vec3.x) + (matVecJ.z * vec3.y) + (matVecK.z * vec3.z);

  return result;
  
}


//  ||====================================================
//  || ROTATION  |||||||||||||||||||||||||||||||||||||||||
//  || Pretty much just multiplying but with preset 
//  || matrices, plus saving the result in the given vec.
//  ||====================================================


// rotate (yeah the pointer is inconsistent but whatever, thats a learning moment)
// note: rotates COUNTER-CLOCKWISE.
void rotateVec2(Vec2 *vecPtr, float radians) {

	// Assemble the rotation matrix.
	Vec2 rotationMat2[2] = {
	              vec2(cos(radians), sin(radians)),
	              vec2(-sin(radians), cos(radians))
							};
	
	// Apply it and save it to the original vector.
	*vecPtr = multVec2Mat2(*vecPtr, rotationMat2);
		
}

// Rotates a vector around the primary XYZ axes.
// Saves to provided pointer. Rotates COUNTER-CLOCKWISE (probably).
void rotateVec3(Vec3* vecPtr, float radX, float radY, float radZ) {

  // Assemble rotation matrices.

  // PITCH (nod up/down).
	Vec3 X_rotationMat3[3] = {
								vec3(1, 0, 0),
                vec3(0, cos(radX), sin(radX)),
								vec3(0, -sin(radX), cos(radX))
							};

  // YAW (turn left/right).
	Vec3 Y_rotationMat3[3] = {
								vec3(cos(radY), 0, -sin(radY)),
                vec3(0, 1, 0),
								vec3(sin(radY), 0, cos(radY))
							};

  // ROLL (tilt) --> Not really gonna be used.
	Vec3 Z_rotationMat3[3] = {
								vec3(cos(radZ), -sin(radZ), 0),
                vec3(-sin(radZ), cos(radZ), 0),
								vec3(0, 0, 1)
							};

  // Apply the matrices.
  // Since I havent written matmult for 3s we do this way.

	*vecPtr = multVec3Mat3(*vecPtr, X_rotationMat3);
	*vecPtr = multVec3Mat3(*vecPtr, Y_rotationMat3);
	*vecPtr = multVec3Mat3(*vecPtr, Z_rotationMat3);

}


//  ||====================================================
//  ||
//  || INTERSECTIONS |||||||||||||||||||||||||||||||||||||
//  || 
//  ||====================================================


Pt3 intersectionLinePlane(Line3 line, Plane plane) {

  // --- 1. (Cartesian eq) get d in Ax + By + Cz + d = 0
  
  /*

  yap sesh (explanation):

  Ax + By + Cz + d = 0

  where A, B, C, are all normal vec's x, y, z

  for the equation to be true (... = 0), the x, y, z must be of a point which exists on the plane.. 
  Ahem, like the point we have from the plane. 

  so Ax + By + Cz can be rewritten as (normal.x)(point.x) + (normal.y)(point.y) + (normal.z)(point.z).. + d = 0

  yeah thats just boring ol dp --> dotprod(normal, point)

  buttt of course stuff is annoying and i cant overload funcs (nor would we really wanna do that, logically incoherent in the grand scheme of things)
  
  so we just hawk tuah type cast that thang and you get this the following

  point -> pointToVector(point)

  and just rearrange and whatever you get the jist

  dotprod(normal, pointToVector(point)) + d = 0
  d = -dotprod(normal, pointToVector(point))

  */

  float d = (-1) * dotVec3(plane.normVec, pt3ToVec3(plane.pt));


  // --- 2. Get the parameter for vector/parametric line equation


  /* 

  idea is super simple but takes a while to follow through so buckle up

  as of now we have:
   - Line --> point, and dir vector
   - Plane --> point, and normal vector --> represented by Ax + By + Cz + d = 0
   - (now we have d too!)

  Pretty much we take point and dir vector, compile parametric equations:

  (Line)
  x = pt.x + (dir.x)(s)
  y = pt.y + (dir.y)(s)
  z = pt.z + (dir.z)(s)  

  Put this into Ax By Cz as x y z
  
  and simplify and rearrange for s gives that which is below. I did the math on paper (might put that on the html) trust its what is below.


  */
  
  float numerator = ((-1 * d) - dotVec3(plane.normVec, pt3ToVec3(line.pt)));
  float denominator = dotVec3(plane.normVec, line.dirVec);

  // denom being 0 just means the line is parallel to the plane and not intersecting; therefore no intersection exists.
  if (denominator == 0) { // uh oh, what if float arithmetic makes it like 0.00000002 - screw that were here for it, bring it on c
    return pt3(0, 0, 0);
  }

  float s =  numerator / denominator; // .."where s belongs to all real numbers" you happy teach?


  // use param eq to build the point and return it
  return pt3(line.pt.x + line.dirVec.x * s, line.pt.y + line.dirVec.y * s, line.pt.z + line.dirVec.z * s);
    
}


//  ||====================================================
//  ||
//  || TRANSFORMATIONS |||||||||||||||||||||||||||||||||||
//  || 
//  ||====================================================


// Note:  Not gonna use cuz when I need to apply translations its actually an inverse transformation and is backwards of this (woah!)
void transformPt(Transformation transformation, Pt3* pt) {

  // Get the translation and rotation for convenience.
  Vec3 translation = transformation.translation;
  Vec3 rotation = transformation.rotation;
  
  // Convert point to vector (since we can transform a vector).
  Vec3 temp = pt3ToVec3(*pt);

  // First rotate that same vector.
  rotateVec3(&temp, rotation.x, rotation.y, rotation.z);

  // Then translate it.
  pt->x = temp.x + translation.x;
  pt->y = temp.y + translation.y;
  pt->z = temp.z + translation.z;

}


//  ||====================================================
//  ||
//  || OPTIMIZATION / CONVENIENCE FUNCTIONS ||||||||||||||
//  || 
//  ||====================================================


// Get the magnitude of a 3D vector.
float magVec3(Vec3 vec3) {

  // Literally just sqrt(vecx^2 ...)
  return sqrt(vec3.x*vec3.x + vec3.y*vec3.y + vec3.z*vec3.z);

}

// Normalizes a given 3D vector.
void normalizeVec3(Vec3* vec3) {

  // Get magnitude of vector.
  float mag = magVec3(*vec3);

  // Divide all components by magnitude.
  vec3->x = (vec3->x / mag);
  vec3->y = (vec3->y / mag);
  vec3->z = (vec3->z / mag);

}

// Converts Pt3 to Vec3.
Vec3 pt3ToVec3(Pt3 pt3) {
  return (Vec3) {
    .x = pt3.x,
    .y = pt3.y,
    .z = pt3.z
  };
}

// Converts Vec3 to Pt3
Pt3 vec3ToPt3(Vec3 vec3) {
  return (Pt3) {
    .x = vec3.x,
    .y = vec3.y,
    .z = vec3.z
  };  
}


//  ||====================================================
//  ||
//  || PRINT FUNCTIONS |||||||||||||||||||||||||||||||||||
//  || 
//  ||====================================================


// Prints formatted 2D vector.
void printVec2(Vec2 vec) {
	printf("<%f, %f>\n", vec.x, vec.y);	
}

// Prints formatted 3D vector.
void printVec3(Vec3 vec) {
	printf("<%f, %f, %f>\n", vec.x, vec.y, vec.z);		
}

// Prints formatted 2x2 matrix.
void printMat2(Vec2 mat2[]) {
	printf("|%f %f|\n", mat2[0].x, mat2[1].x);
	printf("|%f %f|\n", mat2[0].y, mat2[1].y);	
}

// Prints formatted 3x3 matrix.
void printMat3(Vec3 mat3[]) {
	printf("|%f %f %f|\n", mat3[0].x, mat3[1].x, mat3[2].x);		
	printf("|%f %f %f|\n", mat3[0].y, mat3[1].y, mat3[2].y);		
	printf("|%f %f %f|\n", mat3[0].z, mat3[1].z, mat3[2].z);		
}

// Prints formatted 3D point.
void printPt3(Pt3 pt) {
	printf("(%f, %f, %f)\n", pt.x, pt.y, pt.z);		
}
