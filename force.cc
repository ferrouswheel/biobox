#include "biobox.h"

Scalar Force::calcForce() {
	
	Scalar magnitude;

	magnitude = A*cos(B*x + C);

	return magnitude;
}

void Force::incrementX(Scalar amount) {

	x = x + (amount / (2.0 * M_PI));
	if ( (Scalar) (x * B) > ( 2.0 * M_PI ))
		x = x - ( 2.0 * M_PI / B );

}

// ForceMatrix::ForceMatrix(int number) {

// 	int i;

// 	numPoints = number;
// 	forces = (Force**) malloc(sizeof(Force*) * numPoints);
// 	numForces = (int*) malloc(sizeof(int) * numPoints);
	
// 	for (i=0; i < numPoints; i++) {
// 		numForces[i] = 0;
// 		forces[i] = NULL;
// 	}

// }

// void ForceMatrix::addPoint() {

// 	numPoints++;
// 	realloc(forces, sizeof(Force*) * numPoints);
// 	realloc(numForces, sizeof(int) * numPoints);
// 	numForces[numPoints - 1] = 0;

// }

// void ForceMatrix::addForce(int pointIndex, Force newForce) {

// 	numForces[pointIndex]++;
	
// 	forces[pointIndex] = (Force*) realloc(forces[pointIndex],
// 																				sizeof(Force) * numForces[pointIndex]);

// 	forces[pointIndex][numForces[pointIndex] - 1] = newForce;

// }

// Vector* ForceMatrix::calcForce(int pointIndex, Scalar dt) {
// 	int i;
// 	Vector *tempVector = new Vector(0.0,0.0,0.0);

// 	for (i=0; i < numForces[pointIndex]; i++) {
// 		forces[pointIndex][i].incrementX(dt);
// 		*tempVector += *(forces[pointIndex][i].calcForce());
// 	}

// 	return tempVector;

// }
