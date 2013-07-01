#include "biobox.h"

static int lastTicks = 0;

Model::Model(){
	firstMuscle = NULL;
	numMuscles = 0;
	points = NULL;
	numPoints = 0;
}

Model::~Model(){

	// Free memory here. 

}

int Model::addPoint(Scalar x, Scalar y, Scalar z, Scalar weight) {
	int i;

	points = (Point**) realloc(points, (numPoints + 1) * sizeof(Point));
	points[numPoints] = new Point(x, y, z, weight);
	points[numPoints]->index = numPoints;
	
	// if (forceMatrix != NULL) forceMatrix->addPoint();

	// Initially the point is not connected to any muscles.
	for (i=0; i < MAX_MUSCLES_AT_POINT; i++) {
		points[numPoints]->muscles[i] = NULL;
	}

	numPoints++;

	return (numPoints - 1);
}

int Model::addMuscle(Muscle *newMuscle) {
	Muscle *tempMuscle;

	tempMuscle = firstMuscle;

	if (tempMuscle == NULL) {
		firstMuscle = new Muscle(newMuscle);
	} else {
		while ( tempMuscle->next != NULL ) tempMuscle = tempMuscle->next;
		tempMuscle->next = new Muscle(newMuscle);
	}

	numMuscles++;
	return numMuscles - 1;
		
}

int Model::addMuscle(int width, Scalar efficiency, Scalar A, Scalar B, Scalar C) {
	Muscle *tempMuscle;

	tempMuscle = new Muscle;

	tempMuscle->index = numMuscles;
	tempMuscle->width = width;
	tempMuscle->efficiency = efficiency;
	tempMuscle->force = new Force(A, B, C);

	return addMuscle(tempMuscle);
}

void Model::connectMuscle(int muscle, int p1, int p2) {
	Muscle *tempMuscle;
	int i = 0, j = 0;

	// Link Muscle to the two points.
	tempMuscle = findMuscle(muscle);
	tempMuscle->p1 = p1;
	tempMuscle->p2 = p2;
	tempMuscle->point1 = points[p1];
	tempMuscle->point2 = points[p2];

	// Provide a pointer to the muscles that the points are connected to.
	while (points[tempMuscle->p1]->muscles[i] != NULL) i++;
	while (points[tempMuscle->p2]->muscles[j] != NULL) j++;
	if ( i > 4 || j > 4 ) {
        std::cout << "Too many muscles connected to point." << std::endl;
		exit(0);
	}
	points[tempMuscle->p1]->muscles[i] = tempMuscle;
	points[tempMuscle->p2]->muscles[j] = tempMuscle;


	
// 	// Vector from p1 to p2
// 	tempVector = new Vector( points[p2]->x - points[p1]->x,
// 													 points[p2]->y - points[p1]->y,
// 													 points[p2]->z - points[p1]->z );
// 	tempVector->normalize();

// 	// Force going from p1 outwards (vector from p2 to p1)
// 	tempForce = new Force( tempMuscle->function->A,tempMuscle->function->B,
// 												 tempMuscle->function->C, -(*tempVector));
// 	forceMatrix->addForce(p1, *tempForce);

// 	// Force going from p2 outwards (vector from p1 to p2)
// 	tempForce = new Force( tempMuscle->function->A,tempMuscle->function->B,
// 												 tempMuscle->function->C, *tempVector);
// 	forceMatrix->addForce(p2, *tempForce);
	
	
}

Muscle* Model::findMuscle(int index) {
	Muscle *tempMuscle;

	tempMuscle = firstMuscle;
	
	while(tempMuscle != NULL) {
		if (tempMuscle->index == index) return tempMuscle;
		tempMuscle = tempMuscle->next;
	}

	return NULL;
}

int Model::isOneModel() {
	int *checkList;
	int value = 1;
	int i;
	
	checkList = (int*) malloc(sizeof(int)*numPoints);
	for (i=0; i < numPoints; i++) {
		checkList[i] = 0;
	}

	isOneModel(checkList, 0);

	for (i=0; i < numPoints; i++) {
		if (checkList[i] == 0) {
			value = 0;
			break;
		}
	}
	
	free(checkList);

	return value;
}	

void Model::isOneModel(int *checkList, int checkIndex) {

	Muscle *tempMuscle;
	
	checkList[checkIndex] = 1;
	tempMuscle = firstMuscle;

	while (tempMuscle != NULL) {
		if (tempMuscle->p1 == checkIndex) {
				if (checkList[tempMuscle->p2] == 0)
					isOneModel(checkList, tempMuscle->p2);
		} else {
			if (tempMuscle->p2 == checkIndex) {
				if (checkList[tempMuscle->p1] == 0)
					isOneModel(checkList, tempMuscle->p1);
			}
		}
		tempMuscle = tempMuscle->next;
	}
}

int Model::musclesAtPoint(int index) {

	Muscle *tempMuscle;
	int count = 0;

	tempMuscle = firstMuscle;

	while (tempMuscle != NULL) {
		if (tempMuscle->p1 == index || tempMuscle->p2 == index) count++;
		tempMuscle = tempMuscle->next;
	}

	return count;

}

void Model::update() {
	
	int ticks, elapsed, i, j;
	Scalar dt;
	// Scalar contraction, force;
	Vector *tempVector = new Vector(0.0, 0.0, 0.0);
	Vector *tempVector2;
	
	ticks = glutGet(GLUT_ELAPSED_TIME);
	elapsed = ticks - lastTicks;
	dt = (Scalar) elapsed / 1000.0 * SPEED_STEP;
	
	for (i=0; i < numPoints; i++) {

		// Force due to cos function of muscle.
	
		tempVector = points[i]->calcForce(dt);
		*tempVector /= points[i]->weight;
		points[i]->accel = *tempVector;

		// if (i==0) cout << tempVector->x << " " << tempVector->y << " " << tempVector->z << endl;
	}

	delete tempVector;
	tempVector = new Vector(0, -GRAVITY, 0);

	for (i=0; i < numPoints; i++) {
		
		Scalar extension;

// Elasticity
		for (j=0; points[i]->muscles[j] != NULL; j++) {
			extension = points[i]->muscles[j]->currentLength() - points[i]->muscles[j]->origLength();
			tempVector2 = points[i]->muscles[j]->direction(i);

			
			points[i]->accel += SPRING_CONST * extension * (*tempVector2);

		}
// Gravity
		points[i]->accel += *tempVector;
		


		points[i]->displacement += (points[i]->velocity * dt) + (0.5 * points[i]->accel * dt * dt);
		points[i]->velocity += points[i]->accel * dt;

		
// Collisions etc, will be done here.
		if ( points[i]->y + points[i]->displacement.y < FLOOR) {
			points[i]->displacement.y -= (points[i]->y + points[i]->displacement.y) - FLOOR;
			points[i]->velocity.y = -points[i]->velocity.y;
			points[i]->velocity *= (1 - COLLISION_FRICTION); 
		}
		if ( points[i]->z + points[i]->displacement.z < FAR_WALL) {
			points[i]->displacement.z -= (points[i]->z + points[i]->displacement.z) - FAR_WALL;
			points[i]->velocity.z = -points[i]->velocity.z;
			points[i]->velocity *= (1 - COLLISION_FRICTION); 
		}
		if ( points[i]->z + points[i]->displacement.z > NEAR_WALL) {
			points[i]->displacement.z -= (points[i]->z + points[i]->displacement.z) - NEAR_WALL;
			points[i]->velocity.z = -points[i]->velocity.z;
			points[i]->velocity *= (1 - COLLISION_FRICTION); 
		}
		if ( points[i]->x + points[i]->displacement.x < LEFT_WALL) {
			points[i]->displacement.x -= (points[i]->x + points[i]->displacement.x) - LEFT_WALL;
			points[i]->velocity.x = -points[i]->velocity.x;
			points[i]->velocity *= (1 - COLLISION_FRICTION); 
		}
		if ( points[i]->x + points[i]->displacement.x > RIGHT_WALL) {
			points[i]->displacement.x -= (points[i]->x + points[i]->displacement.x) - RIGHT_WALL;
			points[i]->velocity.x = -points[i]->velocity.x;
			points[i]->velocity *= (1 - COLLISION_FRICTION); 
		}
		
	}
	
	lastTicks = ticks;
	
}
	
void Model::draw() {
	Muscle *tempMuscle;

	tempMuscle = firstMuscle;

	glBegin(GL_LINES);
		while (tempMuscle != NULL) {
			
			glLineWidth((GLdouble) tempMuscle->width / 10.0 );
			glVertex3f( (points[tempMuscle->p1]->x + points[tempMuscle->p1]->displacement.x),
						(points[tempMuscle->p1]->y + points[tempMuscle->p1]->displacement.y),
						(points[tempMuscle->p1]->z + points[tempMuscle->p1]->displacement.z));
			glVertex3f( (points[tempMuscle->p2]->x + points[tempMuscle->p2]->displacement.x),
						(points[tempMuscle->p2]->y + points[tempMuscle->p2]->displacement.y),
						(points[tempMuscle->p2]->z + points[tempMuscle->p2]->displacement.z));

			tempMuscle = tempMuscle->next;
		}
	glEnd();

}


