////////////////////////////////////////////////////////////////
//                                                            //
// main.c++                                                   //
// beta version 0.3 - 9/9/97)                                 //
//                                                            //
// George Stetten and Korin Crawford                          //
// copyright given to the public domain                       //
//                                                            //
// Please email comments to stetten@acpub.duke.edu,           //
//                                                            //
////////////////////////////////////////////////////////////////


#include "glutMaster.h"
#include "glutWindow.h"
#include "biobox.h"

GlutMaster		* glutMaster;
Biobox			* world = NULL;

int main(int argc, char* argv[]){

	glutMaster   = new GlutMaster();
	
	world  = new Biobox(glutMaster,
						400, 400,	// height, width
						200, 100,	// initPosition (x,y)
						"Biobox"); 	// title

  
	world->startIdle(glutMaster);   // enable idle function
	world->addOrganism();
	// world->addOrganism();
	glutMaster->CallGlutMainLoop();
}

