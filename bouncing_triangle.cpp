#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init();
void display();
void timer(int t);
static int delay = 1; //milliseconds

GLfloat x[3], y[3], xinc[3], yinc[3];
int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //init GLUT engine
	glutInitWindowSize(500, 500);//window size
	glutCreateWindow("Bouncing Pixel");//create window
	glutDisplayFunc(display);//set display func
	glutTimerFunc(delay, timer, 0);


	init();
	glutMainLoop();//run main loop of GLUT

	return 0;
}

void timer(int t)
{
	glutPostRedisplay(); // call display function which is set by glutDisplayFunc.
	glutTimerFunc(delay, timer, t);
}

void init() {
	srand(time(0));
	glClearColor(1, 1, 1, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	gluOrtho2D(0, 50, 0, 50); // 2D camera (left,right,bottom,top)
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 3; i++) {
		x[i] = rand() % 50; y[i] = rand() % 50;
		xinc[i] = ((GLfloat)(rand() % 1000) / 5000) - 0.1;
		yinc[i] = ((GLfloat)(rand() % 1000) / 5000) - 0.1;
	}

}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f((GLfloat)x[0] / 50, (GLfloat)y[0] / 50, 0);

	for (int i = 0; i < 3; i++) {

		x[i] += xinc[i];
		y[i] += yinc[i];

		if (y[i] >= 50 || y[i] <= 0)
			yinc[i] *= -1;

		if (x[i] >= 50 || x[i] <= 0)
			xinc[i] *= -1;

		glBegin(GL_TRIANGLES);
		glVertex2f(x[i], y[i]);
	}

	glEnd();
	glFlush();
}