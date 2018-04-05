
#define _USE_MATH_DEFINES
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

void init();
void display();
void polygon(int a, int b, int c, int d);
void spin_cube();

static GLfloat theta = 0.0;

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
	glutCreateWindow("Rotating using CTM");//create window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutIdleFunc(spin_cube);//시스템이 여유가 있으면 계속 호출해달라. timer 함수 대체
	glutDisplayFunc(display);//set display func


	init();
	glutMainLoop();//run main loop of GLUT



	return 0;
}

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1, 1, 1, 1);
	//glRotatef(-45, 1, 0,0);
	glOrtho(-2, 2, -2, 2, -10, 10); // 2D camera (left,right,bottom,top)
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glRotatef(theta, 0, 1, 0);

	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(0, 4, 7, 3);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(0, 1, 5, 4);

	//glFlush();
	glutSwapBuffers();
	glFlush();
	//어느버퍼에 작업내용을 넘겨줄건지(front, back 버퍼)



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

void spin_cube()
{
	theta += 2.0;
	if (theta > 360.0) theta -= 360;
	glutPostRedisplay();
	Sleep(5);
}