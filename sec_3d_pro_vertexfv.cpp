
#define _USE_MATH_DEFINES
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void init();
void display();
void timer(int t);
static int delay = 10; //milliseconds
GLfloat angle = 1;

GLfloat toRad(int angle) {
	return (angle * M_PI) / 180;
}

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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	srand(time(0));
	glClearColor(1, 1, 1, 1.0);
	//glRotatef(-45, 1, 0,0);
	glColor3f(1.0, 0.0, 0.0);
	glOrtho(-100, 100, -100, 100, -100, 100); // 2D camera (left,right,bottom,top)
	glEnable(GL_DEPTH_TEST);

}

void rorateMatrix(GLfloat v[3]) {
	GLfloat x = cos(toRad(angle)) * v[0] + sin(toRad(angle)) * v[2];
	GLfloat y = v[1];
	GLfloat z = -sin(toRad(angle)) * v[0] + cos(toRad(angle)) * v[2];
	v[0] = x;
	v[1] = y;
	v[2] = z;
}
void display() {
	GLfloat v0[3] = { 15,15,35 }, v1[3] = { 35,15,35 }, v2[3] = { 35,35,35 }, v3[3] = { 15,35,35 };
	GLfloat v4[3] = { 40,20,15 }, v5[3] = { 20,20,15 }, v6[3] = { 40,40,15 }, v7[3] = { 20,40,15 };


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	angle += 1;
	rorateMatrix(v0),	rorateMatrix(v1),rorateMatrix(v2),rorateMatrix(v3);
	rorateMatrix(v4), rorateMatrix(v5), rorateMatrix(v6), rorateMatrix(v7);



	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3fv(v0); glVertex3fv(v1); glVertex3fv(v2); glVertex3fv(v3);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3fv(v0); glVertex3fv(v1); glVertex3fv(v4); glVertex3fv(v5);
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_POLYGON);
	glVertex3fv(v5); glVertex3fv(v4); glVertex3fv(v6); glVertex3fv(v7);
	glEnd();

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3fv(v7); glVertex3fv(v6); glVertex3fv(v2); glVertex3fv(v3);
	glEnd();

	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex3fv(v0); glVertex3fv(v5); glVertex3fv(v7); glVertex3fv(v3);
	glEnd();

	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3fv(v1); glVertex3fv(v4); glVertex3fv(v6); glVertex3fv(v2);
	glEnd();

	glFlush();



}