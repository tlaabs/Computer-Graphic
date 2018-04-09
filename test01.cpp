
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
	//������۸� , ����, ���� ����
	init();
	glutDisplayFunc(display);//set display func

	glutMainLoop();//run main loop of GLUT



	return 0;
}

void init() {
	glClearColor(1, 1, 1, 1);
	glOrtho(-1, 1, -1, 1, -10, 10);
	glEnable(GL_DEPTH_TEST);//�̰� ���ϸ� Z�࿡ ������� ���߿� �׸� ���� �տ� �׸����� ����.

	

}
/**
GL_MODELVIEW - 3D������ ��ü�� ��ġ�� ���������� ǥ���� ���
GL_PROJECTION - 3D������ ī�޶� ������ ���������� ǥ���� ���


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