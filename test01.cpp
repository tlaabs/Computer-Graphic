
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
	//glutIdleFunc(spin_cube);//�ý����� ������ ������ ��� ȣ���ش޶�. timer �Լ� ��ü
	//������۸� , ����, ���� ����
	init();
	glutDisplayFunc(display);//set display func

	glutMainLoop();//run main loop of GLUT

	return 0;
}

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2, 2, -2, 2, 3, 40);//�����鿡�� �Ÿ� 3���̳�
	glClearColor(1, 1, 1, 1);
	//glOrtho(-1,1, -1, 1, -30, 10);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);//�̰� ���ϸ� Z�࿡ ������� ���߿� �׸� ���� �տ� �׸����� ����.

	

}
/**
GL_MODELVIEW - 3D������ ��ü�� ��ġ�� ���������� ǥ���� ���
GL_PROJECTION - 3D������ ī�޶� ������ ���������� ǥ���� ���


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

	//gluLookAt(1,1,1,0,0,0,0,1,0);
	gluLookAt(0, 0,2, 0, 0, 0, 0, 1, 0);
	glLoadIdentity();
	glTranslatef(0,0,-2);
	glutWireTeapot(0.5);
/*
	glLoadIdentity();

	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
	glTranslatef(0, 0, -2);
	glColor3f(0, 0, 1);
	glutWireTeapot(0.8);
*/

	glutSwapBuffers();
	glFlush();


}