
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
	//glRotatef(-45, 1, 0,0);
	glOrtho(-2, 2, -2, 2, -10, 10); // 2D camera (left,right,bottom,top)
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0,1, 0);
	glRotatef(theta[2], 0,0, 1);
	glScalef(scale, scale, scale);// 정점간의 거리, 즉 벡터의 길이를 늘리고 줄이는 것

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indics);

	//glFlush();
	glutSwapBuffers();
	glFlush();
	//어느버퍼에 작업내용을 넘겨줄건지(front, back 버퍼)



}

//void polygon(int a, int b, int c, int d) {
//	glBegin(GL_POLYGON);
//	glColor3fv(colors[a]);
//	glVertex3fv(vertices[a]);
//
//	glColor3fv(colors[b]);
//	glVertex3fv(vertices[b]);
//
//	glColor3fv(colors[c]);
//	glVertex3fv(vertices[c]);
//
//	glColor3fv(colors[d]);
//	glVertex3fv(vertices[d]);
//	glEnd();
//}

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