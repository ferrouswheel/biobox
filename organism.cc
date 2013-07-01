#include "biobox.h"

#define RANDOM_MAX_POINTS 6.0
#define RANDOM_MUSCLE_MULTIPLY 0.2

Organism::Organism () {

	// No information about model is given, so generate a random
	// lot of points and connecting muscles.

	double randx, randy, randz;	// The co-ordinates of each random point
	double weight;               // The weight of the point.
	int randWidth;				// The width of random muscles
	double randEffi, randA, randB, randC; // The efficiency, and function of muscle
	
	int numberOfPoints, numberOfMuscles;
	int i;

	model = new Model();	// iniatilize the organisms model

	// The organism should have at least 2 points...
	numberOfPoints = 2 + (int) (RANDOM_MAX_POINTS * rand() / RAND_MAX);

    std::cout << "Number of Points = " << numberOfPoints <<std::endl;
	
	for (i=0; i < numberOfPoints; i++) {
	
		// Generate coordinates that should fit in signed byte range
		randx = -128.0 + (255.0 * rand() / RAND_MAX);
		randy = -128.0 + (255.0 * rand() / RAND_MAX);
		randz = -128.0 + (255.0 * rand() / RAND_MAX);
	
		weight = (10.0 * rand() / RAND_MAX);

		model->addPoint(randx, randy, randz, weight);

	    std::cout	<< "Added random point (x,y,z) = (" << randx << ","
				<< randy << "," << randz << ")" <<std::endl;
	}

	// The minimum number of muscles to connect N points is N - 1
	numberOfMuscles =	(numberOfPoints - 1) +
						(int) (numberOfPoints * RANDOM_MUSCLE_MULTIPLY * rand() / RAND_MAX);

    std::cout << "Number of Muscles: " << numberOfMuscles <<std::endl;

	for (i=0; i < numberOfMuscles; i++) {

		// Random muscle width from 1 to 10
		// Random efficiency from 0 to 1
		// Random function Acos(Bx+C) with A = 0 to 1, B = 0 to 10, C = 0 to Pi
		randWidth = 1 + (int) (10.0 * rand() / RAND_MAX);
		randEffi = (double) rand() / RAND_MAX;
		randA = (double) rand() / RAND_MAX;
		randB = (double) rand() / RAND_MAX;
		randC = (double) M_PI * rand() / RAND_MAX;

		model->addMuscle(randWidth, randEffi, randA, randB, randC);

	    std::cout	<< "Added random Muscle: width = " << randWidth
				<< ", efficiency = " << randEffi << ", " << randA << "cos("
				<< randB << "x + " << randC << ")" <<std::endl;
				
	}

	for (i=0; i < numberOfMuscles; i++) { //( !(model->isOneModel()) ) {

		int randMuscle;
		Muscle *tempMuscle;
		Muscle *startMuscle;

		// randomly select one of the muscles
		randMuscle = (int) ((double) numberOfMuscles * rand() / RAND_MAX);
		tempMuscle = model->findMuscle(randMuscle);

		startMuscle = tempMuscle;
		while (tempMuscle->p1 != -1 || tempMuscle->p2 != -1) {
			// Go to the next muscle in the linked list or
			// if at the end then loop back to to the first
			if (tempMuscle->next != NULL)
				tempMuscle = tempMuscle->next;
			else tempMuscle = model->findMuscle(0);

			// if the current tempMuscle is equal to the starting
			// muscle then there are no more muscles availible to connect.
			if (tempMuscle == startMuscle) {
			    std::cout << "Error: No free muscles." <<std::endl;
				exit(0);
			}
		}

		if (tempMuscle->p1 == -1 && tempMuscle->p2 == -1) {
			int index1 = -1, index2 = -1;
			//int leastMuscles;
			//int i;

			index1 = (int) ((double) numberOfPoints * rand() / RAND_MAX);
			index2 = (int) ((double) numberOfPoints * rand() / RAND_MAX);
			if (index1 == index2) {
				if (index2 < (numberOfPoints - 1))
					index2++;
				else index2 = 0;
			}
			
			//for (; i < model->numPoints && index2 == -1; i++) {
			//	if (model->musclesAtPoint(i) == 0) index2 = i;
			//}

			//if (index1 == index2) {
			//    std::cout << "Error: Only one free point" <<std::endl;
			//	exit(1);
			//}

			//if (index1 == -1) {
			//	for (i=0; i < model->numPoints && index1 == -1; i++) {
			//		if (model->musclesAtPoint(i) < 2) index1 = i;
			//	}
			//} else if ( index2 == -1) {
			//	for (; i < model->numPoints && index2 == -1; i++) {
			//		if (model->musclesAtPoint(i) < 2) index2 = i;
			//	}
			//}	

		    std::cout	<< "Connecting muscle " << tempMuscle->index <<
					" to points " << index1 << " and " << index2 <<std::endl;

			model->connectMuscle(tempMuscle->index, index1, index2);
		}
		
	}

    std::cout << model->isOneModel() <<std::endl;



}

int Organism::draw() {

	model->draw();
	  

  return 0;

}

int Organism::update() {

	model->update();

	return 0;
}
