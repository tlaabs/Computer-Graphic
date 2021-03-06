
#define _USE_MATH_DEFINES
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <windows.h>

void init();
void display();
void spin_cube();

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //init GLUT engine
	glutInitWindowSize(500, 500);//window size
	glutCreateWindow("TEST");//create window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//glutIdleFunc(spin_cube);//시스템이 여유가 있으면 계속 호출해달라. timer 함수 대체
	//더블버퍼링 , 색깔, 깊이 버퍼
	init();
	glutDisplayFunc(display);//set display func

	glutMainLoop();//run main loop of GLUT

	return 0;
}

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-2, 2, -2, 2, 1, 40);//투영면에서 거리 3차이남
	glClearColor(1, 1, 1, 1);
	glOrtho(-2,2, -2, 2, -30, 10);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);//이거 안하면 Z축에 상관없이 나중에 그린 것이 앞에 그린것을 가림.

	

}
/**
GL_MODELVIEW - 3D공간에 물체의 배치를 수학적으로 표현한 행렬
GL_PROJECTION - 3D공간에 카메라 설정을 수학적으로 표현한 행렬


*/
void spin_cube()
{
	//printf("x_aixs, z_aixs : %f %f\n", x_axis, z_axis);
	glutPostRedisplay();
	Sleep(5);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glLoadIdentity();

	gluLookAt(0, 0,2, 0, 0, 0, 0, 1, 0);

	//glutWireTeapot(0.5);

	//glColor3f(0, 0, 1);
	//glTranslatef(1, 0, 0);
	//glutWireTeapot(0.5);

	glColor3f(0, 1, 0);
	//glTranslatef(1, 0, 0);
	//glRotatef(90, 0, 1, 0);

	//glRotatef(90, 0, 1, 0);
	glTranslatef(2, 0, 0);
	glutWireTeapot(1);

	glutSwapBuffers();
	glFlush();


}