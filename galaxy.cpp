
#define _USE_MATH_DEFINES
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

void init();
void display();
void spin_cube();
void keyboard_handler(unsigned char key, int x, int y);
void mouse_handler(int btn, int state, int x, int y);

static GLfloat theta[3] = { 0.0,0,0 };
static GLfloat scale = 1;
static int  axis = 1;



//�¾� ������ �׸���
//glutWireSphere
//�״��� �Ȱ��� 
//�������� ���椷
//�¾�׸��� ��Ʈ���� ���ÿ� �־��
//������ �����ؼ� ȸ����


//draw �¾�
//stack �¾� ��Ʈ���� Ǫ��
//rorate(��Ÿ : ����� d���������� ����)
//translate(�¾�,���� �Ÿ���ŭ �̵�)
//roate(��Ÿ,) - ������
//draw ����
//stak ���� ��Ʈ���� Ǫ��
//translate(����-�� �̵��ؼ� �׸���)
//draw ��

//�׸������� ��Ʈ���� pop
//�������������� �Ѿ���� ������ ��ȯ�� ��� ���� �����ؾ���.
int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //init GLUT engine
	glutInitWindowSize(500, 500);//window size
	glutCreateWindow("Rotating using CTM");//create window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);


	//glutIdleFunc(spin_cube);//�ý����� ������ ������ ��� ȣ���ش޶�. timer �Լ� ��ü
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
	glOrtho(-5, 5, -5, 5, -10, 10); // 2D camera (left,right,bottom,top)
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1, 0, 0);
	glutWireSphere(1, 10, 10); //�¾�
	glPushMatrix();

	glTranslatef(3, 0, 0);
	glColor3f(1, 1, 0);
	glutWireSphere(0.5, 10, 10); //����
	glPushMatrix();

	glTranslatef(1, 0, 0);
	glColor3f(0, 0, 1);
	glutWireSphere(0.25, 10, 10);//��

	glFlush();




}

void spin_cube()
{
	theta[axis] += 2.0;
	if (theta[axis] > 360.0) theta[axis] -= 360;
	glutPostRedisplay();
	Sleep(5);
}

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'u') scale += 0.01;
	if (key == 'd') scale -= 0.01;

	if (scale < 0.1) scale = 0.1;
	if (scale > 1.4) scale = 1.4;

}

void mouse_handler(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;

}