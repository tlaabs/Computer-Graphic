#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init();
void display();
void timer(int t);
static int delay = 1; //milliseconds

GLfloat x, y, xinc, yinc;
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
	gluOrtho2D(0,50 , 0, 50); // 2D camera (left,right,bottom,top)
	glClear(GL_COLOR_BUFFER_BIT);

	x = rand() % 50; y = rand() % 50;
	xinc = ((GLfloat)(rand() % 1000) / 5000) - 0.1;
	yinc = ((GLfloat)(rand() % 1000) / 5000) - 0.1;

	printf("xinc : %f, yinc : %f\n", xinc, yinc);
}
void display() {
	glColor3f((GLfloat)x/50, (GLfloat)y/50, 0);

	x += xinc;
	y += yinc;

	if (y >= 50 || y <= 0)
		yinc *= -1;

	if (x >= 50 || x <= 0)
		xinc *= -1;

	glBegin(GL_POINTS);
	glVertex2f(x, y);

	glEnd();
	glFlush();
}