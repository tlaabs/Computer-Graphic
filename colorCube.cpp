
#define _USE_MATH_DEFINES
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void init();
void display();
void polygon(int a, int b, int c, int d);

GLfloat vertices[][3] = {
	{ -1.0,-1.0,-1.0 },{ 1.0,-1.0,-1.0 },{ 1.0,1.0,-1.0 },{ -1.0,1.0,-1.0 },
	{ -1.0,-1.0, 1.0 },{ 1.0,-1.0, 1.0 },{ 1.0,1.0, 1.0 },{ -1.0,1.0, 1.0 }
};

GLfloat colors[][3] = {
	{ 0.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },{ 1.0,1.0, 0.0 },{ 0.0,1.0, 0.0 },
	{ 0.0, 0.0, 1.0 },{ 1.0, 0.0, 1.0 },{ 1.0,1.0, 1.0 },{ 0.0,1.0, 1.0 }
};


int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //init GLUT engine
	glutInitWindowSize(500, 500);//window size
	glutCreateWindow("Color Cube");//create window
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB | GLUT_DEPTH);
	glutDisplayFunc(display);//set display func
	//glutTimerFunc(delay, timer, 0);


	init();
	glutMainLoop();//run main loop of GLUT



	return 0;
}

void init() {
	glClearColor(1, 1, 1, 1.0);
	//glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glTranslatef(0, 0, -5);
	glRotatef(55.26, 1, 0, 0);
	glRotatef(45, 0, 1, 0);
	glOrtho(-2,2,-2,2,-10,10); // 2D camera (left,right,bottom,top)
	glEnable(GL_DEPTH_TEST);

}

void display() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(0, 4, 7, 3);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(0, 1, 5, 4);
	glFlush();



}

void polygon(int a, int b, int c, int d) {
	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glVertex3fv(vertices[a]);

	glColor3fv(colors[b]);
	glVertex3fv(vertices[b]);

	glColor3fv(colors[c]);
	glVertex3fv(vertices[c]);

	glColor3fv(colors[d]);
	glVertex3fv(vertices[d]);
	glEnd();
}