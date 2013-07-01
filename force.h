#include "vector.h"

#ifndef __FORCE__
#define __FORCE__

class Force {
 public:
	Scalar A, B, C, x;
	
	Force(Scalar a, Scalar b, Scalar c) :
		A(a), B(b), C(c), x(0.0) {}
	Force(){}

	void incrementX(Scalar amount);
	Scalar calcForce();

};

#endif

/* class ForceMatrix { */
/*  public: */

/* 	ForceMatrix() { forces = NULL; numForces = NULL; numPoints = 0; } */
/* 	ForceMatrix(int number); */

/* 	void addForce(int pointIndex, Force newForce); */
/* 	void addPoint(); */
/* 	Vector* calcForce(int pointIndex, Scalar dt); */

/*  private: */
/* 	Force **forces; // In form [point][function] */
/* 	int *numForces; */
/* 	int numPoints; */
/* 		}; */
