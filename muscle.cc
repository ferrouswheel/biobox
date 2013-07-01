#include "biobox.h"

Muscle::Muscle(Muscle *newMuscle) {
	index = newMuscle->index;
	width = newMuscle->width;
	efficiency = newMuscle->efficiency;
	force = newMuscle->force;
	p1 = -1;
	p2 = -1;
	point1 = NULL;
	point2 = NULL;
	next = NULL;
}

Scalar Muscle::origLength() {

	if (isConnected()) {
		return sqrt ( (point1->x - point2->x) *
									(point1->x - point2->x) +
									(point1->y - point2->y) *
									(point1->y - point2->y) +
									(point1->z - point2->z) *
									(point1->z - point2->z) );
	}
	return 0;
}

Scalar Muscle::currentLength() {
	
	if (isConnected()) {
		Scalar dx, dy, dz;

		dx = (point1->x + point1->displacement.x) -
			(point2->x + point2->displacement.x);
		
		dy =  (point1->y + point1->displacement.y) -
			(point2->y + point2->displacement.y);
		
		dz = (point1->z + point1->displacement.z) -
			(point2->z + point2->displacement.z);


		return sqrt ( dx * dx + dy * dy + dz * dz );
	}
	return 0;

}

// Gives a vector from {int point} along the muscle
Vector *Muscle::direction(int point) {
	
	if (!isConnected()) return new Vector();
	Vector *tempVector1;
	Vector *tempVector2;
	Vector *returnVector = new Vector();

	tempVector1 = new Vector( (point1->x + point1->displacement.x),
														(point1->y + point1->displacement.y),
														(point1->z + point1->displacement.z) );
	tempVector2 = new Vector( (point2->x + point2->displacement.x),
														(point2->y + point2->displacement.y),
														(point2->z + point2->displacement.z) );

	if (point == p1)
		*returnVector = (*tempVector2 - *tempVector1);
	else if (point == p2)
		*returnVector = (*tempVector1 - *tempVector2);
	else return NULL;
	
	returnVector->normalize();
	return returnVector;
}

int Muscle::isConnected() {

	if (p1 != -1 && p2 != -1) return 1;
	else return 0;
}
