
#define _USE_MATH_DEFINES
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <windows.h>

void init();
void display();

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //init GLUT engine
	glutInitWindowSize(500, 500);//window size
	glutCreateWindow("TEST");//create window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//더블버퍼링 , 색깔, 깊이 버퍼
	init();
	glutDisplayFunc(display);//set display func

	glutMainLoop();//run main loop of GLUT



	return 0;
}

void init() {
	glClearColor(1, 1, 1, 1);
	glOrtho(-1, 1, -1, 1, -10, 10);
	glEnable(GL_DEPTH_TEST);//이거 안하면 Z축에 상관없이 나중에 그린 것이 앞에 그린것을 가림.

	

}
/**
GL_MODELVIEW - 3D공간에 물체의 배치를 수학적으로 표현한 행렬
GL_PROJECTION - 3D공간에 카메라 설정을 수학적으로 표현한 행렬


*/

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 0, 0);

	//draw
	glutWireTeapot(0.5);

	glTranslatef(1, 0, 0);

	glLoadIdentity();
	glutWireTeapot(0.3);

	glutSwapBuffers();
	glFlush();


}