#define _USE_MATH_DEFINES
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void init();
void display();
void timer(int t);
static int delay = 100; //milliseconds

int lon = 0; //경도
int decCount = -5;//경도 증가값

GLfloat toRad(int angle) {
	return (angle * M_PI) / 180;
}
unsigned char buff[240][416];

void timer(int t)
{
	glutPostRedisplay(); // call display function which is set by glutDisplayFunc.
	glutTimerFunc(delay, timer, t);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //init GLUT engine
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);//window size
	glutCreateWindow("2D in 3D Image");//create window
	glutDisplayFunc(display);//set display func
	glutTimerFunc(delay, timer, 0);


	init();
	glutMainLoop();//run main loop of GLUT

	return 0;
}

void init() {
	glClearColor(1, 1, 1, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glOrtho(0, 416, 0, 240, -500, 500);
	glPointSize(8);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTranslatef(0, 0, 0);
	//glRotatef(-45, 1, 0,0); // 회전
	glEnable(GL_DEPTH_TEST);
	FILE *file = fopen("testo.y", "rb");
	fread(buff, 416 * 240, sizeof(char), file); //가로 416 , 세로 240
}
void display() {
	GLfloat x, y, z;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//경도값 새로 고침
	if (lon == 80 || lon == 0)decCount *= -1;
	lon = lon + decCount;
	printf("lon = %d\n", lon);

	glBegin(GL_POINTS);
	//사진과 gl 좌표계 반대.
	for (int i = 0;  i< 240; i++) {
		for (int k = 0; k < 416; k++) {
			GLfloat v = buff[i][k];
			glColor3f(v / 255, v / 255, v / 255);
			x = k * cos(toRad(lon)); //x
			y = 239 - i; //y
			z = k * sin(toRad(lon));
			glVertex3f(x, y, z);
		}
	}

	glEnd();
	glFlush();
}