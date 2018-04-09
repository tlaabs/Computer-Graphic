
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
void keyboard_handler(unsigned char key, int x, int y);
void mouse_handler(int btn, int state, int x, int y);

static GLfloat theta[3] = { 0.0,0,0 };
static GLfloat scale = 1;
static int  axis = 1;
GLfloat x_axis=1,y_axis=1,z_axis=1;


GLfloat vertices[][3] = {
	{ -1.0,-1.0,-1.0 },{ 1.0,-1.0,-1.0 },{ 1.0,1.0,-1.0 },{ -1.0,1.0,-1.0 },
	{ -1.0,-1.0, 1.0 },{ 1.0,-1.0, 1.0 },{ 1.0,1.0, 1.0 },{ -1.0,1.0, 1.0 }
};

GLfloat colors[][3] = {
	{ 0.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },{ 1.0,1.0, 0.0 },{ 0.0,1.0, 0.0 },
	{ 0.0, 0.0, 1.0 },{ 1.0, 0.0, 1.0 },{ 1.0,1.0, 1.0 },{ 0.0,1.0, 1.0 }
};

GLubyte indics[] = {
	0,3,2,1,
	2,3,7,6,
	0,4,7,3,
	1,2,6,5,
	4,5,6,7,
	0,1,5,4 };


int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //init GLUT engine
	glutInitWindowSize(500, 500);//window size
	glutCreateWindow("Rotating using CTM");//create window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);


	glutIdleFunc(spin_cube);//�ý����� ������ ������ ��� ȣ���ش޶�. timer �Լ� ��ü
	glutKeyboardFunc(keyboard_handler);
	glutMouseFunc(mouse_handler);
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
	glOrtho(-4, 4, -4, 4, -10, 10); // 2D camera (left,right,bottom,top)
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(x_axis,y_axis,z_axis, 0, 0, 0, 0, 1, 0);

	//up �����ϸ� X 1�̸� X��������� �������մ�.



	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);
	glScalef(scale, scale, scale);// �������� �Ÿ�, �� ������ ���̸� �ø��� ���̴� ��

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indics);

	//glFlush();
	glutSwapBuffers();
	glFlush();
	//������ۿ� �۾������� �Ѱ��ٰ���(front, back ����)


}

//void polygon(int a, int b, int c, int d) 

void spin_cube()
{
	//theta[axis] += 2.0;
	//if (theta[axis] > 360.0) theta[axis] -= 360;
	printf("x,y,z : %f %f %f\n", x_axis,y_axis,z_axis);
	glutPostRedisplay();
	Sleep(5);
}

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'x') x_axis -= 0.1;
	if (key == 'X') x_axis += 0.1;
	if (key == 'y')  y_axis -= 0.1;
	if (key == 'Y') y_axis += 0.1;
	if (key == 'z') z_axis -= 0.1;
	if (key == 'Z') z_axis += 0.1;


}

void mouse_handler(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;

}