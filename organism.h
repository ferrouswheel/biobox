#include "model.h"

//static char *DNA;

#ifndef __ORGANISM__
#define __ORGANISM__

class Organism {

public:
  Organism();

  Organism *next;

	int update();
	int draw();
	
private:
  Model *model;
  int x, y, z;
  int destx, desty, destz;

};

#endif
