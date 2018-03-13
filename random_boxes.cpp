#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init();
void display();
void timer(int t);
static int delay = 100; //milliseconds
int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //init GLUT engine
	glutInitWindowSize(500, 500);//window size
	glutCreateWindow("Random Boxes");//create window
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
	gluOrtho2D(0, 50, 0, 50); // 2D camera (left,right,bottom,top)
	glClear(GL_COLOR_BUFFER_BIT);
}
void display() {
	int x1, y1, x2, y2, r, g, b;

	x1 = rand() % 50; y1 = rand() % 50;
	x2 = rand() % 50; y2 = rand() % 50;
	r = rand() % 256; g = rand() % 256; b = rand() % 256;

	glColor3d((GLfloat)r / 255, (GLfloat)g / 255, (GLfloat)b / 255);

	glBegin(GL_POLYGON);
	glVertex2f(x1, y1); glVertex2f(x1, y2);
	glVertex2f(x2, y2); glVertex2f(x2, y1);

	glEnd();
	glFlush();
}