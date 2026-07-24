// linlib.c

// Bienvenue a ma bibliotheque d'algebra liniaire (or however the heck its spelt i didnt take french since grade 9)

#include <stdio.h>
#include "linlib.h"
#include <math.h> // TODO  i should prolly just use the pi from this?

Vec2 addVec2(Vec2 vecA, Vec2 vecB) {

	Vec2 result;
	result.x = (vecA.x + vecB.x);
	result.y = (vecA.y + vecB.y);

	return result;
	
}

Vec3 addVec3(Vec3 vecA, Vec3 vecB) {

	Vec3 result;
	result.x = (vecA.x + vecB.x);
	result.y = (vecA.y + vecB.y);
	result.z = (vecA.z + vecB.z);

	return result;
	
}

float dotVec2(Vec2 vecA, Vec2 vecB) {

	float result = (vecA.x * vecB.x) + (vecA.y * vecB.y);

	return result;

}

float dotVec3(Vec3 vecA, Vec3 vecB) {

	float result = (vecA.x * vecB.x) + (vecA.y * vecB.y) + (vecA.z * vecB.z);

	return result;	
	
}

float detMat2(Vec2 mat2[]) {

	Vec2 vecA = mat2[0]; // column vec
	Vec2 vecB = mat2[1]; // column vec

	float result = (vecA.x * vecB.y) - (vecB.x * vecA.y);

	return result;
	
}

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
						(Vec2){.x = vecB.y, .y = vecB.z},
						(Vec2){.x = vecC.y, .y = vecC.z}
					  };						

	float minorA = detMat2(subMatA);

	float termA = (1 * elementA * minorA);


	// TERM 2 (of 3)	


	float elementB = vecB.x;

	Vec2 subMatB[2] = {
						(Vec2){.x = vecA.y, .y = vecA.z},
						(Vec2){.x = vecC.y, .y = vecC.z}
					  };						

	float minorB = detMat2(subMatB);

	float termB = (-1 * elementB * minorB); 
	

	// TERM 3 (of 3)


	float elementC = vecC.x;

	Vec2 subMatC[2] = {
						(Vec2) {.x = vecA.y, .y = vecA.z},	
						(Vec2) {.x = vecB.y, .y = vecB.z}
					  };

	float minorC = detMat2(subMatC);

	float termC = (1 * elementC * minorC);


	// put together and return


	float result = termA + termB + termC;

	return result;
	
}


Vec3 crossVec3(Vec3 vecA, Vec3 vecB) {

	Vec3 result;

	// algorithmically the same as laplace but 
	// dif i dont fully understand yet but maybe i will.


	// i-hat


	Vec2 subMatI[2] = {
						(Vec2) {.x = vecA.y, .y = vecB.y},
						(Vec2) {.x = vecA.z, .y = vecB.z}
					  };

	result.x = (1) * detMat2(subMatI);


	// j-hat


	Vec2 subMatJ[2] = {
						(Vec2) {.x = vecA.x, .y = vecB.x},
						(Vec2) {.x = vecA.z, .y = vecB.z}
					  };


	result.y = (-1) * detMat2(subMatJ); // same bs here with (-1)


	// k-hat


	Vec2 subMatK[2] = {
						(Vec2) {.x = vecA.x, .y = vecB.x},
						(Vec2) {.x = vecA.y, .y = vecB.y}
					  };

	
	result.z = (1) * detMat2(subMatK);


	// return result

	
	return result;

}

// mult mat w vec (note; technically they never need to pass copied values, just pointers work)

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


// rotate (yeah the pointer is inconsistent but whatever, thats a learning moment)
// note: rotates COUNTER-CLOCKWISE
void rotateVec2(Vec2 *vecPtr, float radians) {

	// assemble the rotation matrix
	Vec2 rotationMat2[2] = {
							(Vec2) {.x = cos(radians), .y = sin(radians)},
							(Vec2) {.x = -sin(radians), .y = cos(radians)}
						};

	// apply it and save it to the place
	*vecPtr = multVec2Mat2(*vecPtr, rotationMat2);
		
}



// vec2 / vec3 prints

void printVec2(Vec2 vec) {
	printf("<%f, %f>\n", vec.x, vec.y);	
}

void printVec3(Vec3 vec) {
	printf("<%f, %f, %f>\n", vec.x, vec.y, vec.z);		
}

void printMat2(Vec2 mat2[]) {

	printf("|%f %f|\n", mat2[0].x, mat2[1].x);
	printf("|%f %f|\n", mat2[0].y, mat2[1].y);	

}

void printMat3(Vec3 mat3[]) {
	printf("|%f %f %f|\n", mat3[0].x, mat3[1].x, mat3[2].x);		
	printf("|%f %f %f|\n", mat3[0].y, mat3[1].y, mat3[2].y);		
	printf("|%f %f %f|\n", mat3[0].z, mat3[1].z, mat3[2].z);		
}


