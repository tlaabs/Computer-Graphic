#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init();
void display();
void timer(int t);
static int delay = 1; //milliseconds

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //init GLUT engine
	glutInitWindowSize(500, 500);//window size
	glutCreateWindow("Bouncing Pixel");//create window
	glutDisplayFunc(display);//set display func
	//glutTimerFunc(delay, timer, 0);


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
	glOrtho(0, 50, 0, 50,-50,50); // 2D camera (left,right,bottom,top)
	glClear(GL_COLOR_BUFFER_BIT);

}
void display() {

	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(15,15,35); glVertex3f(35,15,35); glVertex3f(35,35,35); glVertex3f(15,35,35);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(15, 15, 35); glVertex3f(35, 15, 35); glVertex3f(40, 20, 15); glVertex3f(20,20, 15);
	glEnd();

	glColor3f(0 ,0, 1);
	glBegin(GL_POLYGON);
	glVertex3f(20, 20, 15); glVertex3f(40, 20, 15); glVertex3f(40,40,15); glVertex3f(20, 40, 15);
	glEnd();

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(20, 40, 15); glVertex3f(40,40,15); glVertex3f(35,35,35); glVertex3f(15, 35, 35);
	glEnd();

	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex3f(15, 15, 35); glVertex3f(35, 15, 35); glVertex3f(35, 35, 35); glVertex3f(15, 35, 35);
	glEnd();

	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3f(15, 15, 35); glVertex3f(35, 15, 35); glVertex3f(35, 35, 35); glVertex3f(15, 35, 35);
	glEnd();
	
	glFlush();



}