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

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
		glColor3f(1,0,1); // (red,green,blue)
		glVertex3f(-2,-2,-5);
		glVertex3f(2,0,-5);
		glVertex3f(0,2,-5);
	glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);

    (void)glutCreateWindow("GLUT Program");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
