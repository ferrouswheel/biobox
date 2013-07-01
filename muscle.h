#include "vector.h"
#include "force.h"

#ifndef __MUSCLE__
#define __MUSCLE__

class Point;

class Muscle {
public:

	Muscle(){}
	Muscle(Muscle *newMuscle);

	// Returns the length of the muscle
	Scalar origLength();
	Scalar currentLength();
	Vector* direction(int point);
	int isConnected();
	//void incrementX(Scalar dt);

	int index;			// to easily refer to a particular muscle
	int width;
	Scalar efficiency;	// Const * width * efficiency = strength of muscle

	Force *force; // function that the muscle moves to.
	
	Point *point1, *point2; // Direct pointer to the points connected to,
	int p1, p2; 		// Each muscle is connected to two points, refered by index
	Muscle *next;
};

#endif
