#include <stdlib.h>

#if defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


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

double vertices[] = {  0,  .5, 0,
                     -.5, -.5, 0,
                      .5, -.5, 0};

double angle = 0.0f;

void display(void)
{
	glClearColor(0,0,0,.5); //set colour to black
	glEnable(GL_DEPTH_TEST); //enable depth
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity(); // reset transformations
	gluLookAt(	0.0, 0.0, 2.0, //position of eye point (origo)
			0.0, 0.0, 0.0, //position of reference point (where to look)
			0.0, 1.0, 0.0); //direction of up vector
	glRotatef(angle,1.0,1.0,0.0);
	glTranslatef(0.0,0.0,0.0);

	glColor3f(1,0,0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 0, vertices);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	angle+=2.5;
    	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27) //press ESC to exit app
		exit(0);
}

int main(int argc, char** argv)
{
    	glutInit(&argc, argv); //initialize GLUT

	glutInitWindowPosition(300,300); //window position, pixels from top left corner	
    	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    	glutInitWindowSize(640, 480); //window size, width,height in pixels
    	glutCreateWindow("Quack Program"); //create window


    	glutDisplayFunc(display); //requires the window to be painted

    	glutReshapeFunc(reshape);
    	glutIdleFunc(display); // keep calling display (rendering function) when idle

	glutKeyboardFunc(processNormalKeys);

    	glutMainLoop(); //event processing loop

    	return EXIT_SUCCESS;
}
