// Prog26.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//
#include <math.h>
#include <glut.h>
#include <windows.h>

// ---------------------------------------------------------------------------------------------
// Type definition
// ---------------------------------------------------------------------------------------------

typedef struct _object
{
	GLfloat*        vertices;    // vertex array
	GLfloat*        colors;      // color array
	GLubyte*        indices;     // index
	int             nums;        // number of vertices
	GLfloat         theta[3];    // rotation parameter (x, y, z)
	GLfloat         trans[3];		 // translation parameter
	struct _object* child;
	struct _object* next;
} Object;

typedef struct _viewer
{
	GLfloat         eye[3];    // viewer position
	GLfloat         at[3];    // center
	GLfloat         up[3];    // up direction
} Viewer;

typedef struct _window
{
	GLfloat left;
	GLfloat right;
	GLfloat bottom;
	GLfloat top;
	GLfloat _near;
	GLfloat _far;
}Window;


// ---------------------------------------------------------------------------------------------
// Data
// ---------------------------------------------------------------------------------------------

// array 1 (top)
GLfloat vertices1[][3] = { { -0.2,-1.0,-0.2 },{ 0.2,-1.0,-0.2 },{ 0.2,1.0,-0.2 },{ -0.2,1.0,-0.2 },
{ -0.2,-1.0, 0.2 },{ 0.2,-1.0, 0.2 },{ 0.2,1.0, 0.2 },{ -0.2,1.0, 0.2 } };
GLfloat colors1[][3] = { { 0.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },{ 1.0,1.0, 0.0 },{ 0.0,1.0, 0.0 },
{ 0.0, 0.0, 1.0 },{ 1.0, 0.0, 1.0 },{ 1.0,1.0, 1.0 },{ 0.0,1.0, 1.0 } };
GLubyte indices1[] = { 0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4 };

GLfloat vertices2[][3] = { { -0.8,-0.1,-0.1 },{ 0.8,-0.1,-0.1 },{ 0.8,0.1,-0.1 },{ -0.8,0.1,-0.1 },
{ -0.8,-0.1, 0.1 },{ 0.8,-0.1, 0.1 },{ 0.8,0.1, 0.1 },{ -0.8,0.1, 0.1 } };
GLfloat colors2[][3] = { { 0.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },{ 1.0,1.0, 0.0 },{ 0.0,1.0, 0.0 },
{ 0.0, 0.0, 1.0 },{ 1.0, 0.0, 1.0 },{ 1.0,1.0, 1.0 },{ 0.0,1.0, 1.0 } };
GLubyte indices2[] = { 0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4 };

GLfloat vertices3[][3] = { { -0.1,-0.4,-0.1 },{ 0.1,-0.4,-0.1 },{ 0.1,0.4,-0.1 },{ -0.1,0.4,-0.1 },
{ -0.1,-0.4, 0.1 },{ 0.1,-0.4, 0.1 },{ 0.1,0.4, 0.1 },{ -0.1,0.4, 0.1 } };
GLfloat colors3[][3] = { { 0.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },{ 1.0,1.0, 0.0 },{ 0.0,1.0, 0.0 },
{ 0.0, 0.0, 1.0 },{ 1.0, 0.0, 1.0 },{ 1.0,1.0, 1.0 },{ 0.0,1.0, 1.0 } };
GLubyte indices3[] = { 0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4 };

// ---------------------------------------------------------------------------------------------
// Objects
// ---------------------------------------------------------------------------------------------
//���콺 ������ sb1,2 ��� sb3,sb4
Object top;
Object sb1;
Object sb2;
Object sb3;

Viewer v;
Window w;

GLfloat dir[2] = { 1.0,1.0 };

// ---------------------------------------------------------------------------------------------
// Functions
// ---------------------------------------------------------------------------------------------

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

GLfloat clip(GLfloat x)
{
	if (x < 0) return x + 360.0;
	if (x > 360.0) return x - 360.0;
	return x;
}

void spin()
{
	top.theta[2] += 2.0*dir[0];  top.theta[2] = clip(top.theta[2]);
	sb1.theta[2] += 4.0*dir[0];  sb1.theta[2] = clip(sb1.theta[2]);
	sb2.theta[2] += 4.0*dir[1];  sb2.theta[2] = clip(sb2.theta[2]);
	sb3.theta[2] += 8.0*dir[1];  sb3.theta[2] = clip(sb3.theta[2]);
	glutPostRedisplay();
	Sleep(15);
}

// ---------------------------------------------------------------------------------------------
// I/O
// ---------------------------------------------------------------------------------------------

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'x') v.eye[0] -= 0.1; if (key == 'X') v.eye[0] += 0.1;
	if (key == 'y') v.eye[1] -= 0.1; if (key == 'Y') v.eye[1] += 0.1;
	if (key == 'z') v.eye[2] -= 0.1; if (key == 'Z') v.eye[2] += 0.1;
}

void mouse_handler(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON   && state == GLUT_DOWN) dir[0] = -1 * dir[0];
	if (btn == GLUT_MIDDLE_BUTTON   && state == GLUT_DOWN) dir[1] = -1 * dir[1];

}

void draw(Object* p)
{
	// transformation
	glPushMatrix();
	glTranslatef(p->trans[0], p->trans[1], p->trans[2]);
	glRotatef(p->theta[0], 1.0, 0.0, 0.0);
	glRotatef(p->theta[1], 0.0, 1.0, 0.0);
	glRotatef(p->theta[2], 0.0, 0.0, 1.0);

	// draw
	glVertexPointer(3, GL_FLOAT, 0, p->vertices);
	glColorPointer(3, GL_FLOAT, 0, p->colors);
	glDrawElements(GL_QUADS, p->nums, GL_UNSIGNED_BYTE, p->indices); //�簢��, ������ ����, 

	if (p->child) draw(p->child);

	glPopMatrix();
	if (p->next) draw(p->next);
}

void display()
{
	glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 glOrtho(w.left, w.right, w.bottom, w.top, w._near, w._far);
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// setup viewer
	glLoadIdentity();
	gluLookAt(v.eye[0], v.eye[1], v.eye[2], v.at[0], v.at[1], v.at[2], v.up[0], v.up[1], v.up[2]);

	// draw
	draw(&top);

	// flush & swap buffers
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	// GLUT initialization
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog26: multiple objects");

	// call-back functions
	glutIdleFunc(spin);
	glutKeyboardFunc(keyboard_handler);
	glutMouseFunc(mouse_handler);
	glutDisplayFunc(display);

	// enable color/vertex array
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	// object initialization
	top.vertices = &vertices1[0][0];
	top.colors = &colors1[0][0];
	top.indices = &indices1[0];
	top.nums = 24;
	top.theta[0] = top.theta[1] = top.theta[2] = 0;
	top.trans[0] = top.trans[1] = top.trans[2] = 0;

	
	sb1.vertices = &vertices2[0][0];
	sb1.colors = &colors2[0][0];
	sb1.indices = &indices2[0];
	sb1.nums = 24;
	sb1.theta[0] = sb1.theta[1] = sb1.theta[2] = 0;
	sb1.trans[0] = 0;
	sb1.trans[1] = 1;
	sb1.trans[2] = 0;
	sb1.child = 0;
	
	top.child = &sb1;

	sb1.next = &sb2;

	sb2.vertices = &vertices2[0][0];
	sb2.colors = &colors2[0][0];
	sb2.indices = &indices2[0];
	sb2.nums = 24;
	sb2.theta[0] = sb2.theta[1] = sb2.theta[2] = 0;
	sb2.trans[0] = 0;
	sb2.trans[1] = -1;
	sb2.trans[2] = 0;
	sb2.child = &sb3;

	sb3.vertices = &vertices3[0][0];
	sb3.colors = &colors3[0][0];
	sb3.indices = &indices3[0];
	sb3.nums = 24;
	sb3.theta[0] = sb3.theta[1] = sb3.theta[2] = 0;
	sb3.trans[0] = 0.8;
	sb3.trans[1] = 0;
	sb3.trans[2] = 0;
	sb3.next = 0;
	sb3.child = 0;




	// initialize viewer
	v.eye[0] = 0.0; v.eye[1] = 0.0; v.eye[2] = 1.0;
	v.at[0] = 0.0; v.at[1] = 0.0; v.at[2] = 0.0;
	v.up[0] = 0.0; v.up[1] = 1.0; v.up[2] = 0.0;

	w.left = -2, w.right = 2, w.top = 2, w.bottom = -2;
	w._far = 10, w._near = 1;
	init();
	glutMainLoop();

	return 0;
}
