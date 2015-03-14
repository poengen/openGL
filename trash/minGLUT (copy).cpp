#include <stdlib.h>

#if defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
}

void idle(void)
{
    glutPostRedisplay();
}

double vertices[] = {  0,  .5, 0,
                     -.5, -.5, 0,
                      .5, -.5, 0};

void display(void)
{
	glClearColor(0,0,0,.5);
	glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// glLoadIdentity();
	// glRotatef(theta, 0,1,0);
	// glScalef(.99, .99, .99);

	glColor3f(1,0,1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);
    glDrawArrays(GL_TRIANGLES, 0, 3);

/*
	glRotate(
	glBegin(GL_TRIANGLES);
		glColor3f(0,0,1); // (red,green,blue)
		glVertex3f(0,-.5,  0.5);
		glVertex3f(-.5,.5, 0.5);
		glVertex3f(.5 ,.5, 0.5);

glLoadIdentni
glScale

		glColor3f(1,0,1); // (red,green,blue)
		glVertex3f(0,.5,    0);
		glVertex3f(-.5,-.5, 0);
		glVertex3f(.5 ,-.5, 0);
	glEnd();
*/

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);

    (void)glutCreateWindow("Quack Program");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
