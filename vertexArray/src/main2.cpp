// Header files
#include<GL/glew.h>
#include<GL/glut.h> //also includes gl.h
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include "glext.h"

// GLUT CALLBACK functions
void displayCB();
void reshapeCB(int w, int h);
void initGL();
int  initGLUT(int argc, char **argv);
bool initSharedMem();
void clearSharedMem();
void toOrtho();
void toPerspective();
void draw2();

// constants
const int   SCREEN_WIDTH    = 400;
const int   SCREEN_HEIGHT   = 300;

// Global variables
int screenWidth;
int screenHeight;
int drawMode;
int maxVertices;



// cube ///////////////////////////////////////////////////////////////////////
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
//
// vertex coords array for glDrawArrays() =====================================
// A cube has 6 sides and each side has 2 triangles, therefore, a cube consists
// of 36 vertices (6 sides * 2 tris * 3 vertices = 36 vertices). And, each
// vertex is 3 components (x,y,z) of floats, therefore, the size of vertex
// array is 108 floats (36 * 3 = 108).

GLfloat vertices1[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
                       -1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0

                        1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
                        1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0

                        1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
                       -1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0

                       -1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
                       -1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1

                       -1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
                        1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7

                        1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
                       -1, 1,-1,   1, 1,-1,   1,-1,-1 };    // v6-v5-v4

void draw2()
{
    // enble and specify pointers to vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices1);

    glPushMatrix();
    glTranslatef(2, 2, 0);                  // move to upper-right corner

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    // init global vars
    initSharedMem();

    // init GLUT and GL
    initGLUT(argc, argv);
    initGL();


    // check max of elements vertices and elements indices that your video card supports
    // Use these values to determine the range of glDrawRangeElements()
    // The constants are defined in glext.h
    glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &maxVertices);
    
    // the last GLUT call (LOOP)
    // window will be shown and display callback is triggered by events
    // NOTE: this call never return main().
    glutMainLoop(); /* Start GLUT event-processing loop */

    return 0;
}


///////////////////////////////////////////////////////////////////////////////
// initialize GLUT for windowing
///////////////////////////////////////////////////////////////////////////////
int initGLUT(int argc, char **argv)
{
    // GLUT stuff for windowing
    // initialization openGL window.
    // it is called before any other GLUT routine
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);   // display mode

    glutInitWindowSize(screenWidth, screenHeight);  // window size

    glutInitWindowPosition(100, 100);               // window location

    // finally, create a window with openGL context
    // Window will not displayed until glutMainLoop() is called
    // it returns a unique ID
    int handle = glutCreateWindow(argv[0]);     // param is the title of window

    // register GLUT callback functions
    glutDisplayFunc(displayCB);
    glutReshapeFunc(reshapeCB);
    return handle;
}


///////////////////////////////////////////////////////////////////////////////
// initialize OpenGL
// disable unused features
///////////////////////////////////////////////////////////////////////////////
void initGL()
{
    glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable features
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    //glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

     // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);

}

///////////////////////////////////////////////////////////////////////////////
// initialize global variables
///////////////////////////////////////////////////////////////////////////////
bool initSharedMem()
{
    screenWidth = SCREEN_WIDTH;
    screenHeight = SCREEN_HEIGHT;



    drawMode = 0; // 0:fill, 1: wireframe, 2:points
    maxVertices = 0;

    return true;
}


///////////////////////////////////////////////////////////////////////////////
// clean up global vars
///////////////////////////////////////////////////////////////////////////////
void clearSharedMem()
{


}

//=============================================================================
// CALLBACKS
//=============================================================================

void displayCB()
{
    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // save the initial ModelView matrix before modifying ModelView matrix
    glPushMatrix();

    draw2();        // with glDrawArrays()

    glPopMatrix();

    glutSwapBuffers();
}

void reshapeCB(int w, int h)
{
    screenWidth = w;
    screenHeight = h;
}


/*



GLfloat vertices[] = {-0.5, -0.5, 0.0, 0.5, 0.5, -0.5};

void generateGeometry( void ){
	GLfloat vertices[] = {-0.5, -0.5, 0.0, 0.5, 0.5, -0.5};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
}

void initGPUBuffers( void ){
	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers( 1, &buffer );
	glBindBuffer( GL_ARRAY_BUFFER, buffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW );
}

void myDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT); // clear screen
	glDrawArrays(GL_LINE_LOOP, 0, 3); // draw the points
	glFlush(); // force rendering to show
	glDisableClientState(GL_VERTEX_ARRAY);
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,150);
	glutCreateWindow("my first attempt");
	glewInit();

	glutDisplayFunc(myDisplay);
	//glutReshapeFunc(myReshape);
	//glutMouseFunc(myMouse);
	//glutKeyboardFunc(myKeyboard);

	glewInit();
	generateGeometry();
	initGPUBuffers();
	glutMainLoop();

	return 0;
}


*/
