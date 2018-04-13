
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
static GLfloat scale = 0.4;
static int  axis = 1;
GLfloat x_axis = 0, y_axis = 0, z_axis = 0;
int flag = 1;
int w = 2;
int h = 2;
float toRad(float angle) {
	return (M_PI / 180)*angle;
}

int down_x, down_y;
int up_x, up_y;
GLfloat rotate_x = 0;
static GLfloat mouse_x = 0, mouse_y = 0;

//--------------------------
static GLfloat camera_x = 0; static GLfloat camera_z = 2;

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
	glutCreateWindow("FPS");//create window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //색 입히기 OFF

	glutIdleFunc(spin_cube);//시스템이 여유가 있으면 계속 호출해달라. timer 함수 대체
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
	glFrustum(-2, 2, -2, 2, 1, 20);
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	/*glPushMatrix();*/
	//glRotated(0, 0, 1, 0);

	//gluLookAt(x_axis, 0, z_axis,mouse_x + x_axis, mouse_y, z_axis - 1, 0, 1, 0);

	gluLookAt(camera_x, 0, 2 + camera_z, sin(toRad(mouse_x*45))*100, mouse_y*100, -cos(toRad(mouse_x*45))*100,0, 1, 0);

	glColor3f(1, 0, 0);
	glutWireTeapot(0.5);

	//오른쪽 4 파란 큐브
	glTranslatef(4, 0, 0);
	glColor3f(0, 0, 1);
	glutWireCube(0.8);

	glTranslatef(-8, 0, 0);
	glColor3d(0, 0, 0);
	glutWireCube(0.8);

	//원점
	glPopMatrix();
	glTranslatef(0, 0, -6);
	glColor3f(0, 1, 0);
	glutWireCube(0.6);

	glTranslatef(5, 0, 0);
	glColor3d(153, 0, 76);
	glutWireCone(1, 1, 10, 10);


	glutSwapBuffers();
	glFlush();

}


void spin_cube()
{

	glutPostRedisplay();
	Sleep(5);
}

void keyboard_handler(unsigned char key, int x, int y)
{
	printf("mouse _X : %f\n", mouse_x);
	if (key == 'a') {//왼
		camera_x += -cos(toRad(mouse_x*45));
		camera_z += -sin(toRad(mouse_x*45));
	}
	if (key == 'd') {//오
		camera_x += cos(toRad(mouse_x * 45));
		camera_z += sin(toRad(mouse_x * 45));
	}
	if (key == 'w') {//앞
		camera_x += sin(toRad(mouse_x*45));
		camera_z += -cos(toRad(mouse_x*45));
	}
	if (key == 's') {//뒤
		camera_x += -sin(toRad(mouse_x*45));
		camera_z += cos(toRad(mouse_x*45));
	}

}

void mouse_handler(int btn, int state, int x, int y)
{

	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		down_x = x;
		down_y = y;

	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		up_x = x;
		up_y = y;

		mouse_y += (down_y - up_y) / 250.0;
		mouse_x += (up_x - down_x) / 250.0;
		printf("mouse_y : %f\n", mouse_y);
	}


}