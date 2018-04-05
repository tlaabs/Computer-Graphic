
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
GLfloat scale = 0.2f;
GLfloat scaleIncre = 0.01f;

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
	scale += scaleIncre;
	if (scale >= 1.0 || scale <= 0.1)scaleIncre *= -1;
	printf("scale : %f", scale);
}

void init() {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	//srand(time(0));
	glClearColor(1, 1, 1, 1.0);
	//glRotatef(-45, 1, 0,0);
	glColor3f(1.0, 0.0, 0.0);
	//glOrtho(-100, 100, -100, 100, -100, 100); // 2D camera (left,right,bottom,top)
	glOrtho(-30, 30, -30, 30, -30, 30);
	glEnable(GL_DEPTH_TEST);

}


void rorateMatrix(GLfloat v[3]) {
	GLfloat x = (v[0] -25);
	GLfloat y = (v[1] - 25);
	GLfloat z = (v[2] - 25); //z +스면 가까워진다?

	GLfloat _x = cos(toRad(angle)) * (x) + sin(toRad(angle)) * (z);
	GLfloat _y = (y);
	GLfloat _z = -sin(toRad(angle)) * (x) + cos(toRad(angle)) * (z);
	v[0] = _x * scale;
	v[1] = _y * scale;
	v[2] = _z* scale;

}
void display() {
	GLfloat v0[3] = { 15,15,35 }, v1[3] = { 35,15,35 }, v2[3] = { 35,35,35 }, v3[3] = { 15,35,35 };
	GLfloat v4[3] = { 40,20,15 }, v5[3] = { 20,20,15 }, v6[3] = { 40,40,15 }, v7[3] = { 20,40,15 };
	//GLfloat t[3] = { -25,-25,-25 };


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	angle += 1;
	rorateMatrix(v0), rorateMatrix(v1), rorateMatrix(v2), rorateMatrix(v3);
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