#ifndef __BIOBOX__
#define __BIOBOX__

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "organism.h"
#include "glutMaster.h"

// Currently all cc files include this file,
// this is mainly because I am lazy. I will try
// organise it better when it has some functionality.

// The speed at which cosine function increments
// This should later be set to a variable that the
// user can change. 
#define FUNC_SPEED (M_PI_4 / 4)

#define FLOOR -128.0
#define CEILING 256.0
#define FAR_WALL -256.0
#define LEFT_WALL -256.0
#define RIGHT_WALL 256.0
#define NEAR_WALL 256.0

// The Biobox class, is a child of GlutWindow
// written by someone else (read README.glutWindow.txt
// for more info). It extends it by also including
// functions and variables to describe the whole
// biobox environment, like organisms etc.
// It is the "world" of the program.
// Thought: Perhaps the window functions should be
// a seperate class... 
class Biobox : public GlutWindow {

public:
	int		height, width;                // The height and width of the window.
	int		initPositionX, initPositionY; // The initial position of the window.

	Biobox(GlutMaster * glutMaster,
				 int setWidth, int setHeight,
				 int setInitPositionX, int setInitPositionY,
				 const char * title);

	~Biobox();

	// GLUT functions:
 	void CallBackDisplayFunc(void);
	void CallBackReshapeFunc(int w, int h);   
	void CallBackIdleFunc(void);
	void CallBackMouseFunc(int button, int state, int x, int y);
	void startIdle(GlutMaster * glutMaster); // Enables the GLUT idle function.

	// Biobox related functions:
	int addOrganism();
	int drawBox();

private:		
	Organism *firstOrganism; // The first Organism in a linked list.

};

#endif
