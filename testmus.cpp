#include <stdlib.h>
#include <iostream>

#if defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;


GLdouble vertices[] = {-0.5,-0.5,0,0.5,-0.5,0,0,0.5,0};

GLubyte colors[] = {	100, 0, 0,
    			200, 200, 10,
   			250, 0, 100 };

GLshort indices[] = {0,1,2};


void reshape(int w, int h);
void display(void);
void processNormalKeys(unsigned char key, int x, int y);
void minGRID();

int main(int argc, char** argv)
{

    	glutInit(&argc, argv); //initialize GLUT

	glutInitWindowPosition(300,300); //window position, pixels from top left corner	
    	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    	glutInitWindowSize(1000, 1000); //window size, width,height in pixels (640,480)
    	glutCreateWindow("Quack Program"); //create window

    	glutDisplayFunc(display); //requires the window to be painted

    	glutReshapeFunc(reshape);
    	glutIdleFunc(display); // keep calling display (rendering function) when idle

	glutKeyboardFunc(processNormalKeys);

    	glutMainLoop(); //event processing loop

    	return EXIT_SUCCESS;
}

void display(void)
{
	glClearColor(0,0,0,.5); //set colour to black
	glEnable(GL_DEPTH_TEST); //enable depth
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity(); // reset transformations
	gluLookAt(	0.0, 0.0, 4.0, //position of eye point (origo)
			0.0, 0.0, 0.0, //position of reference point (where to look)
			0.0, 1.0, 0.0); //direction of up vector


	glColor3f(1,0,0);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glPushMatrix();

	glColorPointer( 3, GL_UNSIGNED_BYTE, 0, colors );
	glVertexPointer(3, GL_DOUBLE, 0, vertices);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, indices);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
    	glutSwapBuffers();
}



void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27) //press ESC to exit app
		exit(0);
}

void reshape(int w, int h) //NESCESSARY IF WINDOW NOT CHANGED?
{
    	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	glMatrixMode(GL_PROJECTION); // Use the Projection Matrix
	glLoadIdentity(); // Reset Matrix
	glViewport(0, 0, w, h); // Set the viewport to be the entire window

	// Set the correct perspective.
	gluPerspective(45,ratio,1,100); //last two defines near and far clipping plane

	glMatrixMode(GL_MODELVIEW); // Get Back to the Modelview
}
