
#define _USE_MATH_DEFINES
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <windows.h>

void init();
void display();
void spin_cube();

static int t_time = 0;

//�ѽð� 0.1��
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


	glutIdleFunc(spin_cube);//�ý����� ������ ������ ��� ȣ���ش޶�. timer �Լ� ��ü
	//glutKeyboardFunc(keyboard_handler);
	//glutMouseFunc(mouse_handler);
	glutDisplayFunc(display);//set display func


	init();
	glutMainLoop();//run main loop of GLUT



	return 0;
}

void init() {

	glClearColor(1, 1, 1, 1);

	glOrtho(-1, 1, -1, 1, -10, 10); // 2D camera (left,right,bottom,top)

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glColor3f(1.0, 0.3, 0.3);
	glutWireSphere(0.2, 20, 16);
	glPushMatrix();//�⺻ ��ǥ 
	
	glRotatef(1.0/24 * t_time, 0.0, 1.0, 0.0);//���� ����


	glTranslatef(0.7, 0.0, 0.0);
	glPushMatrix();

	glRotatef(23.5, 0,0,1);//���� ��

	glRotatef(360/24 * t_time, 0.0, 1.0, 0.0);//���� ����
	glColor3f(0.5, 0.6, 0.7);
	glutWireSphere(0.1, 10, 8);
	

	glPopMatrix();
	glRotatef(0.5 * t_time, 0, 1, 0);//�� ����
	glTranslatef(0.2, 0.0, 0.0);
	glColor3f(0.9, 0.8, 0.2);
	glutWireSphere(0.04, 10, 8);
	
	glPopMatrix();
	glPopMatrix();
	
	glutSwapBuffers();

	glFlush();


}

void spin_cube()
{

	t_time += 1;

	int day = 0, hour = 0;
	day = t_time / 24;
	hour = t_time % 24;

	printf("t_time  %d�� %d �ð� �������ϴ�.\n", day, hour);

	glutPostRedisplay();
	Sleep(1);
}