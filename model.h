
#include "muscle.h"
#include "point.h"

#ifndef __MODEL__
#define __MODEL__

// Another lot of definitions to control the speed of
// cos functions... should be made redundant
// eventually.
#define SPEED_STEP 15.0
#define COLLISION_FRICTION 0.10
#define AIR_FRICTION 0.01
#define SPRING_CONST 0.005
#define GRAVITY 3.0

class Model {
public:
	Model ();
	~Model ();

	int addPoint(Scalar x, Scalar y, Scalar z, Scalar weight);
	int addMuscle(int width, Scalar efficiency, Scalar A, Scalar B, Scalar C);
	int addMuscle(Muscle* newMuscle);
	void connectMuscle(int muscle, int p1, int p2);
	int musclesAtPoint(int index);
	Muscle * findMuscle(int index);
	void isOneModel(int *checkList, int checkIndex);
	int isOneModel();
	// void initForceMatrix();

	void draw();
	void update();

	int numPoints;			// the number of points in the array
	
private:
	Muscle *firstMuscle;	// to be used like a linked list
	int numMuscles;
	Point **points; 		// to be used as an array
	// ForceMatrix *forceMatrix;
	
};

#endif
