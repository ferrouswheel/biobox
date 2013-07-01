#include "muscle.h"
#include "vector.h"

#ifndef __POINT__
#define __POINT__

#define MAX_MUSCLES_AT_POINT 5

class Muscle;

class Point {
public:

	// Various constructors:
	Point()
		: x(0), y(0), z(0), weight(0.0) {	}
	
	Point(signed char x, signed char y, signed char z, Scalar weight)
		: x(x), y(y), z(z), weight(weight){	}
	
	Point(Vector point, Scalar weight)
		: x((signed char) point.x), y((signed char) point.y), z((signed char) point.z),
		weight(weight) {}
	
	void setAccel(Vector accel);
	Vector* calcForce(Scalar dt);

	signed char x, y, z;    // initial point.
	Vector displacement;
	Vector velocity;
	Vector accel;
	Scalar weight;
	int index;

	Muscle *muscles[MAX_MUSCLES_AT_POINT];
};

#endif
