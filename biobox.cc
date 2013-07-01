#include "biobox.h"

Biobox::Biobox(GlutMaster * glutMaster,
				int setWidth, int setHeight,
				int setInitPositionX, int setInitPositionY,
				const char * title) {

	firstOrganism = NULL;

	// Set up the initial window dimensions:
	width  = setWidth;
	height = setHeight;
	initPositionX = setInitPositionX;
	initPositionY = setInitPositionY;

	// Pass these to GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(initPositionX, initPositionY);
  
	// Get glutMaster to create a new window for this class
	glutMaster->CallGlutCreateWindow(title, this);

	// Set GL variables/stuff
	glEnable(GL_LINE_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glViewport(0, 0, width, height);
	glPolygonMode(GL_FRONT, GL_FILL);
}

Biobox::~Biobox(){
	glutDestroyWindow(windowID);
}

void Biobox::CallBackDisplayFunc(void) {
	Organism *tempOrganism;

	static double spin = 0;

	if (spin < 360)
		spin = spin + .25;
	else spin = 0;

	// Clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();

	glTranslatef(0, 0, -400); // Move objects back from camera

	drawBox();

	glColor4f(0.7, 0.0, 0.0, 1.0);

	// glRotatef(spin, 1.0, 1.0, 0.0);
		
	tempOrganism = firstOrganism;

	// Draw all the organisms in the box.
	while (tempOrganism != NULL) {
		tempOrganism->draw();
		tempOrganism = tempOrganism->next;
	}

	glPopMatrix();
	glutSwapBuffers();
}

int Biobox::drawBox() {

	
	glBegin(GL_QUADS);

	// Draw Floor
  	glColor3f(0.6, 0.6, 0.6); // Grey
    glVertex3f( LEFT_WALL, FLOOR, NEAR_WALL );
		glVertex3f( RIGHT_WALL, FLOOR, NEAR_WALL );
		glVertex3f(	RIGHT_WALL, FLOOR, FAR_WALL );
		glVertex3f( LEFT_WALL, FLOOR, FAR_WALL );

	// Draw far wall
		glColor3f(0.8, 0.8, 0.8); // Lighter Grey
		glVertex3f( RIGHT_WALL, CEILING, FAR_WALL );
		glVertex3f( LEFT_WALL, CEILING, FAR_WALL );
		glVertex3f( LEFT_WALL, FLOOR, FAR_WALL );
		glVertex3f( RIGHT_WALL, FLOOR, FAR_WALL );

  // Draw left wall
		glColor3f(0.9, 0.9, 0.9);
		glVertex3f( LEFT_WALL, CEILING, FAR_WALL );
		glVertex3f( LEFT_WALL, CEILING, NEAR_WALL );
		glVertex3f( LEFT_WALL, FLOOR, NEAR_WALL );
		glVertex3f( LEFT_WALL, FLOOR, FAR_WALL );

	// Draw right wall
		glVertex3f( RIGHT_WALL, CEILING, NEAR_WALL );
		glVertex3f( RIGHT_WALL, CEILING, FAR_WALL );
		glVertex3f( RIGHT_WALL, FLOOR, FAR_WALL );
		glVertex3f( RIGHT_WALL, FLOOR, NEAR_WALL );

	glEnd();

	return 0;

}
	

void Biobox::CallBackReshapeFunc(int w, int h) {

 	width = w;
	height= h;
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 10.0, 1500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

void Biobox::CallBackMouseFunc(int button, int state, int x, int y) {

	extern GlutMaster *glutMaster;
	
	switch (button) {
  case GLUT_LEFT_BUTTON:
    if(state == GLUT_DOWN)
      glutMaster->EnableIdleFunction();
    break;
  case GLUT_MIDDLE_BUTTON:
    if(state == GLUT_DOWN)
      glutMaster->DisableIdleFunction();
    break;
  default:
    break;
  }
}

void Biobox::CallBackIdleFunc(void) {
	Organism *tempOrganism;

	tempOrganism = firstOrganism;

	// Let each Organism update themselves.
	while (tempOrganism != NULL) {
		tempOrganism->update();
		tempOrganism = tempOrganism->next;
	}

	glutPostRedisplay();
}

void Biobox::startIdle(GlutMaster * glutMaster) {
	glutMaster->SetIdleToCurrentWindow();
	glutMaster->EnableIdleFunction();
}

int Biobox::addOrganism() {
	Organism *tempOrganism;

	tempOrganism = firstOrganism;

	if (tempOrganism == NULL) {
		firstOrganism = new Organism();
		tempOrganism = firstOrganism;
	} else {
		while ( tempOrganism->next != NULL ) tempOrganism = tempOrganism->next;
		tempOrganism->next = new Organism();
		tempOrganism = tempOrganism->next;
	}

	return 0;

}
