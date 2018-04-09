
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
GLfloat x_axis = 3, y_axis = 3, z_axis = 3;
static int flag = 1;

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

	glClearColor(1, 1, 1, 1);
	
	if (flag == 1) {
		glFrustum(-2, 2, -2, 2, 2, 20);
		glScalef(1, 1, 1);
		printf("glFrustum \n");
	}
	else {
		glOrtho(-2, 2, -2, 2, -10, 10); // 2D camera (left,right,bottom,top)
		glScalef(0.4, 0.4, 0.4);
		printf("ortho \n");
	}
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(x_axis, y_axis, z_axis, 0, 0, 0, 0, 1, 0);
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);
	// 정점간의 거리, 즉 벡터의 길이를 늘리고 줄이는 것

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indics);

	glutSwapBuffers();
	glFlush();
	//어느버퍼에 작업내용을 넘겨줄건지(front, back 버퍼)


}

void spin_cube()
{
	printf("x,y,z : %f %f %f\n", x_axis, y_axis, z_axis);
	glutPostRedisplay();
	Sleep(10);
}

void keyboard_handler(unsigned char key, int x, int y)
{

	if (key == 'x')x_axis -= 0.1;

	if (key == 'X') x_axis += 0.1;
	if (key == 'y')  y_axis -= 0.1;
	if (key == 'Y') y_axis += 0.1;
	if (key == 'z') z_axis -= 0.1;
	if (key == 'Z') z_axis += 0.1;

	if (key == 'p') {
		flag *= -1;
		init();
	}


}

void mouse_handler(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;

}