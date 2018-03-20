#define _USE_MATH_DEFINES
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void init();
void display();

GLfloat toRad(int angle);

GLfloat toRad(int angle) {
	return (M_PI / 180) * angle;
}
int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //init GLUT engine
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);//window size
	glutCreateWindow("Sphere");//create window
	glutDisplayFunc(display);//set display func


	init();
	glutMainLoop();//run main loop of GLUT

	return 0;
}

void init() {
	glClearColor(1, 1, 1, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glOrtho(-2, 2, -2, 2, -2, 2); 
		
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //색 입히기 OFF
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTranslatef(0, 0, 0);
	//glRotatef(-45, 1, 0,0); // 회전
	glEnable(GL_DEPTH_TEST);
}
void display() {
	GLfloat x, y, z;

	//북극점
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, -1);
	for (int lon = -180; lon <= 180; lon += 20) {
		glColor3f(fabs(lon) / 180, 0, 0);
		x = sin(toRad(lon)) * cos(toRad(-80));
		y = cos(toRad(lon)) * cos(toRad(-80));
		z = sin(toRad(-80));
		glVertex3f(x, y, z);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (int lat = -80; lat < 80; lat += 20) {
		for (int lon = -180; lon <= 180; lon += 20) {
			glColor3f(fabs(lon) / 180, 0, 0);
			x = sin(toRad(lon)) * cos(toRad(lat));
			y = cos(toRad(lon)) * cos(toRad(lat));
			z = sin(toRad(lat));
			glVertex3f(x, y, z);
			printf("x ,y ,z : %f %f %f\n", x, y, z);

			//위도가 올라가야지
			x = sin(toRad(lon)) * cos(toRad(lat + 20));
			y = cos(toRad(lon)) * cos(toRad(lat + 20));
			z = sin(toRad(lat+20));
			glVertex3f(x, y, z);
			printf("x ,y ,z : %f %f %f \n", x, y, z);
			printf("\n");
		}
	}
	glEnd();

	//남극점
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 1);
	for (int lon = -180; lon <= 180; lon += 20) {
		glColor3f(fabs(lon) / 180, 0, 0);
		x = sin(toRad(lon)) * cos(toRad(80));
		y = cos(toRad(lon)) * cos(toRad(80));
		z = sin(toRad(80));
		glVertex3f(x, y, z);
	}
	glEnd();
	glFlush();
}