#include <glut.h>
#include <math.h>
#include <stdio.h>
struct Light {
	GLfloat pos[4];
	GLfloat amb[4];
	GLfloat dif[4];
	GLfloat spe[4];
};
struct Light light = {
	{ 0.0,2.0,2.0,1.0 },
	{ 1.0,1.0,1.0,1.0 },
	{ 1.0,1.0,1.0,1.0 },
	{ 1.0,1.0,1.0,1.0 }
};
struct Material {
	GLfloat amb[4]; // ambient ambient
	GLfloat dif[4]; // diffuse diffuse
	GLfloat spe[4]; // specular specular
	GLfloat shi; // shininess shininess
};
struct Material mat = {
	{ 0.2, 0.0, 0.0, 1.0 },
	{ 1.0, 1.0, 0.0, 1.0 },
	{ 1.0, 1.0, 0.0, 1.0 },
	{ 100.0 },
};
GLfloat E = 0;
GLint mode = 0, level = 4;
GLfloat R = 1.0092;
GLfloat V[][3] = { { 0.58,0.58,0.58 },{ -0.58,-0.58,0.58 },{ 0.58,-0.58,-0.58 },{ -0.58,0.58,-0.58 } };
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-4.0, 4.0, -4.0, 4.0, -10.0, 10.0);
	gluLookAt(2, 2, 2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_POSITION, light.pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light.amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.spe);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GLU_FLAT);
}
GLfloat inter(GLfloat a, GLfloat b) {
	GLfloat x;
	x = (a + b) / 2;
	return x;
}
void sphere(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat d[], GLfloat e[], GLfloat f[], int l) {
	void triangle(GLfloat[], GLfloat[], GLfloat[], int);
	if (l > level) {
		return;
	}
	triangle(a, d, e, l);
	triangle(c, e, f, l);
	triangle(b, f, d, l);
	triangle(d, f, e, l);
}
void triangle(GLfloat a[], GLfloat b[], GLfloat c[], int l)
{
	GLfloat v[3][3], V[3];
	int i;

	if (mode != 2)
		glShadeModel(GL_FLAT);
	else
		glShadeModel(GL_SMOOTH);
	if (mode == 0)
		glBegin(GL_LINE_LOOP);
	else
		glBegin(GL_POLYGON);

	if (l == level) {
		glNormal3fv(a); glVertex3fv(a);
		glNormal3fv(b); glVertex3fv(b);
		glNormal3fv(c); glVertex3fv(c);
		glEnd();
	}
	else {
		for (i = 0; i < 3; i++) {
			v[0][i] = inter(a[i], b[i]);
			v[1][i] = inter(a[i], c[i]);
			v[2][i] = inter(b[i], c[i]);
		}
		for (i = 0; i < 3; i++) {
			V[i] = sqrt(pow(v[i][0], 2) + pow(v[i][1], 2) + pow(v[i][2], 2));
		}
		for (i = 0; i < 3; i++) {
			v[0][i] *= R / V[0];
			v[1][i] *= R / V[1];
			v[2][i] *= R / V[2];
		}
		sphere(a, b, c, v[0], v[1], v[2], ++l);
	}
}
void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'a')
		E += 1;
	if (key == 's')
		E -= 1;
	if (key == 'x')
		light.pos[0] -= 0.1;
	if (key == 'X')
		light.pos[0] += 0.1;
	if (key == 'y')
		light.pos[1] -= 0.1;
	if (key == 'Y')
		light.pos[1] += 0.1;
	if (key == 'z')
		light.pos[2] -= 0.1;
	if (key == 'Z')
		light.pos[2] += 0.1;
	if (key == 'm') {
		mode++;
		mode %= 3;
	}
	if (key == 'n') {
		level--;
		if (level < 0)
			level = 0;
	}
	if (key == 'N') {
		level++;
		if (level > 8)
			level = 8;
	}

	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat.amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat.dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat.spe);
	glMaterialf(GL_FRONT, GL_SHININESS, mat.shi);
	glRotatef(E, 0, 1, 0);
	//triangle(V[0], V[1], V[2], 0);
	triangle(V[3], V[2], V[1], 0);
	//triangle(V[0], V[3], V[1], 0);
	//triangle(V[0], V[2], V[3], 0);
	glLightfv(GL_LIGHT0, GL_POSITION, light.pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light.amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.dif);
	glTranslatef(light.pos[0], light.pos[1], light.pos[2]);
	glutSolidSphere(0.2, 10, 10);
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("HW4:sphere shading");
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}