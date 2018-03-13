#include <glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

void init();
void display();
static int delay = 1;

void timer(int t);
void recTriangle(int n, GLfloat* a, GLfloat* b, GLfloat* c);

GLfloat initPoints[3][2] = { { 0,0 },{ 25,50 },{ 50,0 } };
int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Recursive Triangles");
	glutDisplayFunc(display);
	glutTimerFunc(delay, timer, 0);

	init();
	glutMainLoop();

	return 0;
}

void timer(int t) {
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}

void init() {
	srand(time(NULL));
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(0.0, 50.0, 0.0, 50.0); //그림그리는 도화지 좌표 설정
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	//glBegin(GL_TRIANGLES);
	//glVertex2fv(initPoints[0]); //Vertex 2 floating vertex
	//glVertex2fv(initPoints[1]); //Vertex 2 floating vertex
	//glVertex2fv(initPoints[2]); //Vertex 2 floating vertex
	//glEnd();
	//glFlush();

}

void display() {

	glColor3f(1.0, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(25, 50);
	glVertex2f(50, 0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(10, 10);
	glVertex2f(35, 60);
	glVertex2f(60, 10);
	glEnd();
	glFlush();
	//recTriangle(4, initPoints[0], initPoints[1], initPoints[2]);
}

void recTriangle(int n, GLfloat v1[], GLfloat v2[], GLfloat v3[]) {
	GLfloat midPoints[3][2];
	if (n < 0)
		return;
	midPoints[0][0] = (v1[0] + v2[0]) / 2; midPoints[0][1] = (v1[1] + v2[1]) / 2;
	midPoints[1][0] = (v1[0] + v3[0]) / 2; midPoints[1][1] = (v1[1] + v3[1]) / 2;
	midPoints[2][0] = (v2[0] + v3[0]) / 2; midPoints[2][1] = (v2[1] + v3[1]) / 2;

	glBegin(GL_TRIANGLES);
	glVertex2fv(midPoints[0]);
	glVertex2fv(midPoints[1]);
	glVertex2fv(midPoints[2]);
	glEnd();
	glFlush();

	recTriangle(n - 1, v1, midPoints[0], midPoints[1]);
	recTriangle(n - 1, midPoints[0], v2, midPoints[2]);
	recTriangle(n - 1, midPoints[1], midPoints[2], v3);
}