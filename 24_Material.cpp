
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
void timer();
void keyboard_handler(unsigned char key, int x, int y);
void cube();


GLfloat vertices[][3] = {
	{ -1.0,-1.0,-1.0 },{ 1.0,-1.0,-1.0 },{ 1.0,1.0,-1.0 },{ -1.0,1.0,-1.0 },
	{ -1.0,-1.0, 1.0 },{ 1.0,-1.0, 1.0 },{ 1.0,1.0, 1.0 },{ -1.0,1.0, 1.0 }
};

//GLfloat colors[][3] = {
//	{ 0.5, 0.5, 0.5 },{ 0.5, 0.5, 0.5 },{ 0.5, 0.5, 0.5 },{ 0.5, 0.5, 0.5 },
//	{ 0.5, 0.5, 0.5 },{ 0.5, 0.5, 0.5 },{ 0.5, 0.5, 0.5 },{ 0.5, 0.5, 0.5 }
//};

typedef struct {
	GLfloat pos[4];  // position position
	GLfloat amb[4];  // ambient ambient
	GLfloat dif[4]; // diffuse diffuse
	GLfloat spe[4]; // specular specular
} Light;

Light light = {
	{ 3,3,3,1 }, // position // position
	{ 1,1,1,1 }, // ambient // ambient
	{ 1,1,1,1 }, // diffuse // diffuse
	{ 1,1,1,1 }// specular // specular
};


typedef struct {
	GLfloat amb[4];  // ambient ambient
	GLfloat dif[4]; // diffuse diffuse
	GLfloat spe[4]; // specular specular
	GLfloat shi;
} Material;

Material mat0 = {
	{ 0.2,0.2,0.2, 1.0 },
	{ 1,1,1,1 }, 
	{ 1,1,1,1 }, 
	{100}
};

Material mat1 = {
	{ 0.2,0,0, 1.0 }, // position // position
	{ 1,0,0,1 }, //diffuse
	{ 1,0,0,1 }, // spe
	{ 100 }// shi
};

Material mat2 = {
	{0,0.2,0,1.0 },
	{ 0,1,0,1 }, 
	{ 0,1,0,1 },
	{ 100 }
};

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //init GLUT engine
	glutInitWindowSize(500, 500);//window size
	glutCreateWindow("Color Cube");//create window
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutIdleFunc(timer);//시스템이 여유가 있으면 계속 호출해달라. timer 함수 대체
	glutDisplayFunc(display);//set display func
							 //glutTimerFunc(delay, timer, 0);

	glutKeyboardFunc(keyboard_handler);


	init();
	glutMainLoop();//run main loop of GLUT



	return 0;
}

void init() {
	glClearColor(1, 1, 1, 1.0);
	//glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-5, 5, -5, 5, -10, 10); // 2D camera (left,right,bottom,top)
	gluLookAt(2, 2, 2, 0, 0, 0, 0, 1, 0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glShadeModel(GL_FLAT); //default smooth
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//gluLookAt(2, 2, 2, 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, light.pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light.amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.spe);

	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat0.amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0.dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat0.spe);
	glMaterialf(GL_FRONT, GL_SHININESS, mat0.shi);

	cube();

	glLoadIdentity();
	glTranslatef(-3, 0, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat1.amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat1.dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat1.spe);
	glMaterialf(GL_FRONT, GL_SHININESS, mat1.shi);

	cube();

	glLoadIdentity();
	glTranslatef(3, 0, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat2.amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat2.dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat2.spe);
	glMaterialf(GL_FRONT, GL_SHININESS, mat2.shi);

	cube();
	glLoadIdentity();
	glTranslatef(light.pos[0], light.pos[1], light.pos[2]);
	glutSolidSphere(0.2, 10, 10);

	glutSwapBuffers();
	glFlush();

}

void cube() {
	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(0, 4, 7, 3);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(0, 1, 5, 4);
}

void timer()
{
	glutPostRedisplay();
	Sleep(5);
}

void normalVec(GLfloat *n) {
	GLfloat x = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
	if (x > 0.0) for (int i = 0; i < 3; i++)n[i] /= x;
}

void polygon(int a, int b, int c, int d) {
	GLfloat nor[3];

	nor[0] = vertices[a][0] + vertices[b][0] + vertices[c][0] + vertices[d][0];
	nor[1] = vertices[a][1] + vertices[b][1] + vertices[c][1] + vertices[d][1];
	nor[2] = vertices[a][2] + vertices[b][2] + vertices[c][2] + vertices[d][2];

	normalVec(nor);

	//glNormal3fv(nor);
	glBegin(GL_POLYGON);
	glNormal3fv(nor);
	/*glColor3fv(colors[a]);*/

	glVertex3fv(vertices[a]);

	//glColor3fv(colors[b]);

	glVertex3fv(vertices[b]);

	//glColor3fv(colors[c]);
	glVertex3fv(vertices[c]);

	//glColor3fv(colors[d]);
	glVertex3fv(vertices[d]);
	glEnd();

}

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'x') light.pos[0] += -0.1;
	if (key == 'X') light.pos[0] += 0.1;
	if (key == 'y') light.pos[1] += -0.1;
	if (key == 'Y') light.pos[1] += 0.1;
	if (key == 'z') light.pos[2] += -0.1;
	if (key == 'Z') light.pos[2] += 0.1;



}