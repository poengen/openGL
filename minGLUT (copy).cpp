#include <stdlib.h>
#include <iostream>
#include <math.h>

#if defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

#define PI 3.14159

int const n = 100;//maks 256 for GLshort // THIS IS WHERE I DEFINE THE GRID SIZE
GLfloat vertices[3*n*n]; //3*n^2		n=3(27), n=4(48)
GLshort indices[6*(n-1)*(n-1)]; //6*(n-1)^2	n=3(24), n=4(54)
GLubyte colors[3*n*n];

double angless = 0.0f;
void reshape(int w, int h);
void display(void);
void processNormalKeys(unsigned char key, int x, int y);
void minGRID();

// angle of rotation for the camera direction
float angle = 0.0f;

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;

// XZ position of the camera
float x=0.0f, z=5.0f;


void mouseButton(int button, int state, int x, int y);
void mouseMove(int x, int y);
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}


int main(int argc, char** argv)
{

	minGRID();

    	glutInit(&argc, argv); //initialize GLUT

	glutInitWindowPosition(300,300); //window position, pixels from top left corner	
    	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    	glutInitWindowSize(1000, 1000); //window size, width,height in pixels (640,480)
    	glutCreateWindow("Quack Program"); //create window


    	glutDisplayFunc(display); //requires the window to be painted

    	glutReshapeFunc(reshape);
    	glutIdleFunc(display); // keep calling display (rendering function) when idle

	glutKeyboardFunc(processNormalKeys);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

    	glutMainLoop(); //event processing loop

    	return EXIT_SUCCESS;
}

void display(void)
{

	if (deltaMove)
		computePos(deltaMove);


	glClearColor(0,0,0,.5); //set colour to black
	glEnable(GL_DEPTH_TEST); //enable depth
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity(); // reset transformations
	gluLookAt(	0.5*x, 0.5, 2.0*z, //position of eye point (origo)
			x+0.5*x, 0.5, z+lz, //position of reference point (where to look)
			0.0, 1.0, 0.0); //direction of up vector
	//glRotatef(angle,1.0,0.0,0.0);
	//glTranslatef(0.0,0.0,0.0);

	glColor3f(0,1,1);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glPushMatrix();

	glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawElements(GL_TRIANGLES, 6*(n-1)*(n-1), GL_UNSIGNED_SHORT, indices);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);

	angless+=2.5;
    	glutSwapBuffers();
}

void minGRID() {
	double h = 1./(double)(n-1);
	double xx[n];
	
	for (int i=0; i<n; i++){
		xx[i] = i*h; // = -1+i*2*h; (shift quadrant)	
	}

	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			vertices[3*i+3*n*j] = xx[i]; //x-coordinate
			vertices[3*n*i+3*j+1] = xx[i]; //y-coordinate

			vertices[3*n*i+3*j+2] = sin(PI*xx[i])*sin(PI*xx[j]); //z-coordinate

			colors[3*i+3*n*j] = 200*(1-sin(PI*xx[i])*sin(PI*xx[j]))+55; //red color
			colors[3*n*i+3*j+1] = 800*(1-sin(PI*xx[i])*sin(PI*xx[j]))*sin(PI*xx[i])*sin(PI*xx[j])+55; //green color
			colors[3*n*i+3*j+2] = 200*sin(PI*xx[i])*sin(PI*xx[j])+55; //blue color			
		}
	}

	int index;
	int a;
	for (int k=0; k<2; k++){
		index = 0;
		for (int l=0; l<n-1; l++){
			index = l*n;
			for (int j=0; j<3; j++){
				if (k==0 && j==1){ index = index - (n-2); }

				else if (k==0 && j==2){ index++; }
				else if (k==1 && j==1){ index++; }
				else if (k==1 && j==2){ index = index - (n-2); }
				
				for(int i=0; i<n-1; i++){
					a = 3*k*(n-1)*(n-1) + 3*l*(n-1) + j + 3*i;
					indices[a] = index;
					index++;
				}
			}
		}
	}
// TAKES AWAY UPPER OR LOWER TRIANGLES
//for (int i=0; i<(6*(n-1)*(n-1))/2; i++){indices[i]=0;}
//for (int i=(6*(n-1)*(n-1))/2; i<6*(n-1)*(n-1); i++){indices[i]=0;}
// PRINT FUNCTION
//for (int i=0; i<6*(n-1)*(n-1); i++){cout << indices[i] << endl;}
//for (int i=0; i<3*n*n; i++){cout << vertices[i] << endl;}
	
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

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_DOWN) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else  { //state = GLUT_DOWN
			xOrigin = x;
		}
	}
}

void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}


