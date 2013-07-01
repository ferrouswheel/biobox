#include "biobox.h"

void Point::setAccel(Vector accel) { this->accel = accel; }

Vector* Point::calcForce(Scalar dt) {
	int i = 0;
	Vector *tempVector = new Vector(0.0,0.0,0.0);

	while (muscles[i] != NULL) {
		muscles[i]->force->incrementX(dt);
		*tempVector += muscles[i]->force->calcForce() * -(*(muscles[i]->direction(index)));
		i++;
	}

	return tempVector;
	
}

