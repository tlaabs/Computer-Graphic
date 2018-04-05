
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

//한시간 0.1초
//태양 원점에 그리기
//glutWireSphere
//그다음 똑같이 
//프레임의 변경ㅇ
//태양그리고 메트릭스 스택에 넣어놔
//프레임 변경해서 회전해


//draw 태양
//stack 태양 메트릭스 푸시
//rorate(세타 : 사용자 d누를때마다 변경)
//translate(태양,지구 거리만큼 이동)
//roate(세타,) - 공전임
//draw 지구
//stak 지구 메트릭스 푸시
//translate(지구-달 이동해서 그리기)
//draw 달

//그리기전에 매트릭스 pop
//파이프라인으로 넘어갓을때 정점의 변환이 어떻게 될지 생각해야함.
int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //init GLUT engine
	glutInitWindowSize(500, 500);//window size
	glutCreateWindow("Rotating using CTM");//create window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);


	glutIdleFunc(spin_cube);//시스템이 여유가 있으면 계속 호출해달라. timer 함수 대체
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
	glPushMatrix();//기본 좌표 
	
	glRotatef(1.0/24 * t_time, 0.0, 1.0, 0.0);//지구 공전


	glTranslatef(0.7, 0.0, 0.0);
	glPushMatrix();

	glRotatef(23.5, 0,0,1);//지구 축

	glRotatef(360/24 * t_time, 0.0, 1.0, 0.0);//지구 자전
	glColor3f(0.5, 0.6, 0.7);
	glutWireSphere(0.1, 10, 8);
	

	glPopMatrix();
	glRotatef(0.5 * t_time, 0, 1, 0);//달 공전
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

	printf("t_time  %d일 %d 시간 지났습니다.\n", day, hour);

	glutPostRedisplay();
	Sleep(1);
}