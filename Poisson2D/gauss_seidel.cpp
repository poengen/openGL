#include <iostream>
#include <armadillo>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <cstdlib>
#include <stdio.h>
#include <sys/time.h>

using namespace std;

//Macros
#define PI 3.14159
#define IX(i,j) ((n+2)*(i)+(j))
#define RED(i,j) ((3)*(i)+(3)*(n+2)*(j))
#define SWAP(x0,x) {double * tmp=x0;x0=x;x=tmp;}

//global variables
struct timeval lastTime;

int n, K; ///HUSK
GLdouble *vertices;
GLshort *indices;
GLubyte *colors;

double *x;

double *dens, *dens_prev, *s;
double dt, diff, visc, force, source;
int omx, omy, mx, my, size;
double a, c, h;


GLdouble *createVertices (int n);
GLshort *createIndices (int n);
GLubyte *createColors (int n);
double *createDensity(int n);
void makeGrid(int n, GLdouble *vertices, GLshort *indices, GLubyte *colors);
void display(void);
void processNormalKeys(unsigned char key, int x, int y);

void makeGlut(void);
void mouseClick(int button, int state, int x, int y);
void mouseDrag(int x, int y);
void mouseMove(int x, int y);
void mouseAction(int x, int y);

void printIndices(int n, GLshort *indices);

void draw(){
	int i,j;
	for (i=0; i<n+2; i++){
		for (j=0; j<n+2; j++){
				colors[RED(i,j)] = dens_prev[IX(i,j)];
		}
	}
}

void diffuse(){
	int i, j, k;

		for ( k=0 ; k<K ; k++ ) {
		for ( i=1 ; i<n+1 ; i++ ) {
			for ( j=1 ; j<n+1 ; j++ ) {

	dens[IX(i,j)] = (c*(dens_prev[IX(i,j)] + dt*s[IX(i,j)] - a*(dens[IX(i-1,j)]+dens_prev[IX(i+1,j)]+dens[IX(i,j-1)]+dens_prev[IX(i,j+1)])));

			}
		}
	/*
	printf("dens = \n");
	for (i=0; i<n+2; i++){
		for (j=0; j<n+2; j++){
			printf("|%f",dens[IX(i,j)]);
		}
		printf("|\n");
	}
	*/
	//SWAP(dens, dens_prev);
	}
}

void get_from_UI(){
	int i;

	for(i = 0; i<size; i++){
		s[i] = 0;
	}
	
	dens_prev[IX(mx,my)] = source;

	omx = mx;
	omy = my;
}

long getTimePassed() {
	struct timeval time_now;
	long seconds, useconds;
	gettimeofday(&time_now, NULL);
	seconds  = time_now.tv_sec  - lastTime.tv_sec;
	useconds = time_now.tv_usec - lastTime.tv_usec;
	lastTime = time_now;
	return ((seconds*1000) + useconds/1000.0);
}


void myDriver( void ){

	//get_from_UI(); //add mouse input to s (source buffer);
	//diffuse();
	//SWAP(dens,dens_prev);
	//draw();
	/*
	for (int i=0; i<size; i++){
		s[i] = 0;
		//dens[i] = 0;
		//dens_prev[i] = 0;
	}
	*/
	/*
	int i,j,k;
	for (i=0; i<n+2; i++){
		for (j=0; j<n+2; j++){
			//dens_prev[IX(i,j)] = 0.0;//250*sin(PI*x[i])*sin(PI*x[j]);
			//dens[IX(i,j)] = 0.0;
			//s[IX(i,j)] = 0.0;//2*PI*PI*sin(PI*x[i])*sin(PI*x[j]);
		}
	}

	//s[IX(1,1)]=0;

	//boundary fix
	
	for (i=0; i<n+2; i++){
		s[IX(i,0)] = 0;
		s[IX(0,i)] = 0;
		s[IX(i,n+1)] = 0;
		s[IX(n+1,i)] = 0;
		dens_prev[IX(i,0)] = 0;
		dens_prev[IX(0,i)] = 0;
		dens_prev[IX(i,n+1)] = 0;
		dens_prev[IX(n+1,i)] = 0;
		
	}
	*/
	//draw();

	long t = getTimePassed();
	diffuse();

	SWAP(dens, dens_prev);
	draw();

	t = getTimePassed();
	cout << "Time in myDriver() = " << t << endl;

	glutPostRedisplay();
}

void runthis(){

	//draw();
}

int main(int argc, char** argv)
{


	int i, j, k;

	n = atoi(argv[1]);
	K = atoi(argv[2]);

	if (argc < 2){
		printf("Error: need a problem size as first argument\n");
		return 1;
	}

	n = atoi(argv[1]); //Max limit 256
	if (n>254){
		printf("Error: problem size cannot exceed 254\n");
		return 1;
	}

	h = 1/((double)n+1);
	dt = 0.1; diff = -0.000001; visc = 0.0; force = 5.0; source = 250.0;
	a = dt*diff*n*n;
	c = 1/(1-4*a);

	size = (n+2)*(n+2);

	dens		= (double *) malloc ( size*sizeof(double) );	
	dens_prev	= (double *) malloc ( size*sizeof(double) );
	s		= (double *) malloc ( size*sizeof(double) );

	//declare and allocate memory for Vertex Buffer Objects (VBO)

	vertices = createVertices(3*(n+2)*(n+2));
	indices = createIndices(6*(n+1)*(n+1));
	colors = createColors(3*(n+2)*(n+2));

	//initialize VBO
	makeGrid(n+2, vertices, indices, colors);

	//////

	x = (double *) malloc ( (n+2)*sizeof(double) );
	
	for (i=0; i<n+2; i++){
		x[i] = i*h;	
	}

	//////

	//runthis();
	
	// TAKES AWAY UPPER OR LOWER TRIANGLES
	for (int i=0; i<(6*(n+1)*(n+1))/2; i++){indices[i]=0;} //lower
	//for (int i=(6*(n+1)*(n+1))/2; i<6*(n+1)*(n+1); i++){indices[i]=0;} //upper


	//GLUT
    	glutInit(&argc, argv); //initialize GLUT
	makeGlut();
    	glutMainLoop(); //event processing loop

    	return EXIT_SUCCESS;
}

GLdouble *createVertices (int n)
{
	GLdouble *vector;
	vector = (GLdouble *)malloc(n*sizeof(GLdouble));
	return vector;
}

GLshort *createIndices (int n)
{
	GLshort *vector;
	vector = (GLshort *)malloc(n*sizeof(GLshort));
	return vector;
}

GLubyte *createColors (int n)
{
	GLubyte *vector;
	vector = (GLubyte *)malloc(n*sizeof(GLubyte));
	return vector;
}


void makeGrid(int n, GLdouble *vertices, GLshort *indices, GLubyte *colors) {
	double h = 1./(double)(n-1);
	double x[n];
	
	for (int i=0; i<n; i++){
		x[i] = -1+i*2*h; //= i*h; (shift quadrant)	
	}

	double temp_z;
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			vertices[3*i+3*n*j] = x[i]; //x-coordinate
			vertices[3*n*i+3*j+1] = x[i]; //y-coordinate
			//temp_z = cos(0.5*PI*x[i])*cos(0.5*PI*x[j]); // sin(PI*x[i])*sin(PI*x[j]);
			vertices[3*n*i+3*j+2] = 0;//temp_z; //z-coordinate

			colors[3*i+3*n*j] = 0;//255*temp_z; //red color (0-255) strongest when z=0
			colors[3*n*i+3*j+1] = 0; //green color (0-255) strongest when z=0.5
			colors[3*n*i+3*j+2] = 0; //blue color (0-255) strongest when z=1
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
					indices[a] = index; //this loop creates the index buffer
					index++;
				}
			}
		}
	}
}

void mouseClick(int button, int state, int x, int y) {
    //cout << "Mouse click at " << x << ", " << y << " button " << button << "  state " << state << endl;
}

void mouseDrag(int x, int y) {
     	//cout << "Mouse drag at " << x << ", " << y << endl;
	mouseAction(x,y);
}

void mouseAction(int x, int y){
	double pph = 1000/(double)(n+1); //OK
	double closeX = (double)x/pph;
	double closeY = (double)(1000-y)/pph;
	mx = round(closeX); my = round(closeY);
	dens_prev[IX(mx,my)] = source;
	//cout<<"Mouse move at: ("<< x <<", " << y <<"). Index is: ("<< closeX <<", "<< closeY <<")."<<endl;
	//dens[RED(ix,iy)] = 255; //red color
}

void display(void)
{
	glClearColor(0,0,0,.5); //set background colour to black
	glEnable(GL_DEPTH_TEST); //enable depth
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); // reset transformations
	glColor3f(0,1,1);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glPushMatrix();
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);
	glVertexPointer(3, GL_DOUBLE, 0, vertices);
	glDrawElements(GL_TRIANGLES, 6*(n+1)*(n+1), GL_UNSIGNED_SHORT, indices);
	glPopMatrix();
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
    	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27) //press ESC to exit app
		exit(0);
}

void makeGlut(void){
	glutInitWindowPosition(300,300); //window position, pixels from top left corner	
    	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //display mode
    	glutInitWindowSize(1000, 1000); //window size, width, height in pixels (640,480)
    	glutCreateWindow("Quack Program"); //create window
    	

	glutDisplayFunc(display); //requires the window to be painted
	//glutIdleFunc(display); // keep calling display (rendering function) when idle
	glutIdleFunc(myDriver); //does the numerical simulation, this is where the program operates mostly
	glutKeyboardFunc(processNormalKeys);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseDrag);
}

void printIndices(int n, GLshort *indices){
	int i;
	for (i=0; i<6*(n+1)*(n+1); i++){
		cout << indices[i] << endl;
	}
}












