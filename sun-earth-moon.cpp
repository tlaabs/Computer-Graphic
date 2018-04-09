
#define _USE_MATH_DEFINES
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <windows.h>

void init();
void display();
void timer();
static int time = 0;

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //init GLUT engine
	glutInitWindowSize(500, 500);//window size
	glutCreateWindow("Galaxy");//create window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);


	glutIdleFunc(timer);//시스템이 여유가 있으면 계속 호출해달라. timer 함수 대체

	glutDisplayFunc(display);//set display func


	init();
	glutMainLoop();//run main loop of GLUT



	return 0;
}

void init() {

	glClearColor(1, 1, 1, 1);

	glOrtho(-1, 1, -1, 1, -10, 10);

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 0.3, 0.3);
	glutWireSphere(0.2, 20, 16);
	glPushMatrix();//기본 좌표 
	
	glRotatef(360.0/(24*365) * time, 0.0, 1.0, 0.0);//지구 공전 - 태양 프레임 기준


	glTranslatef(0.7, 0.0, 0.0); //지구프레임
	//glRotatef(-360.0 / (24 * 365) * time , 0.0, 1.0, 0.0);//자전축 바뀌지 않게.

	glPushMatrix();

	glRotatef(23.5, 0, 0, 1);//지구프레임에서 z축으로 자전축을 기울이고

	glRotatef(360.0/24 * time, 0.0, 1.0, 0.0);//기울어진 지구 프레임에서 지구를 
	
	glColor3f(0.5, 0.6, 0.7);
	glutWireSphere(0.1, 10, 8);
	

	glPopMatrix(); //태초의 지구프레임
	glRotatef(360.0 / (30 * 24) * time, 0, 1, 0);//태초의 지구프레임에서 달을 공전시킴
	glTranslatef(0.2, 0.0, 0.0);
	glColor3f(0.9, 0.8, 0.2);
	glutWireSphere(0.04, 10, 8);
	
	glPopMatrix();
	
	glutSwapBuffers();

	glFlush();


}

void timer()
{

	time += 1; // hour

	int day = 0, hour = 0;
	day = time / 24;
	hour = time % 24;

	printf("%d일 %d 시간 지났습니다.\n", day, hour);

	glutPostRedisplay();
	Sleep(1);
}