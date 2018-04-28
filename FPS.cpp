
#define _USE_MATH_DEFINES
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

void init();
void display();
void timer();
void keyboard_handler(unsigned char key, int x, int y);
void mouse_handler(int btn, int state, int x, int y);

float toRad(float angle) {
	return (M_PI / 180)*angle;
}

int down_x, down_y; //mouse down x, y point
int up_x, up_y; // mouse up x,y point

static GLfloat mouse_x = 0, mouse_y = 0; //mouse rotate angle

static GLfloat camera_x = 0; static GLfloat camera_z = 0;//camera position

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //init GLUT engine
	glutInitWindowSize(500, 500);//window size
	glutCreateWindow("FPS");//create window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutIdleFunc(timer);
	glutDisplayFunc(display);//set display func
	glutKeyboardFunc(keyboard_handler);
	glutMouseFunc(mouse_handler);

	init();
	glutMainLoop();//run main loop of GLUT

	return 0;
}

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2, 2, -2, 2, 2, 20);
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	/*
	camera is located at (0,0,2)
	sin() is too small (floating number 0 <= x <= 1), so multiply 100.
	*/
	gluLookAt(camera_x, 0, 2 + camera_z, sin(toRad(mouse_x*45))*100, mouse_y*100, -cos(toRad(mouse_x*45))*100,0, 1, 0);
	
	glColor3f(1, 0, 0);
	glutWireTeapot(0.5);

	glTranslatef(4, 0, 0);
	glColor3f(0, 0, 1);
	glutWireCube(0.8);

	glTranslatef(-8, 0, 0);
	glColor3d(0, 0, 0);
	glutWireCube(0.8);

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


void timer()
{

	glutPostRedisplay();
	Sleep(5);
}

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'a') {//left
		camera_x += -cos(toRad(mouse_x*45));
		camera_z += -sin(toRad(mouse_x*45));
	}
	if (key == 'd') {//right
		camera_x += cos(toRad(mouse_x * 45));
		camera_z += sin(toRad(mouse_x * 45));
	}
	if (key == 'w') {//toward
		camera_x += sin(toRad(mouse_x*45));
		camera_z += -cos(toRad(mouse_x*45));
	}
	if (key == 's') {//back
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
	}

}