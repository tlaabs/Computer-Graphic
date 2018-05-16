// Prog31.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include <glut.h>

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
	//GLubyte texflag[3];
	struct _object* next;
	struct _object* child;

} Object;

typedef struct _viewer
{
	GLfloat         eye[3];  // viewer position
	GLfloat         at[3];  // center
	GLfloat         up[3];  // up direction
} Viewer;

typedef struct _texture
{
	GLubyte* rgb; // 8bit
	int width;
	int height;
}Texture;



// ---------------------------------------------------------------------------------------------
// Data
// ---------------------------------------------------------------------------------------------

// array 1 (box)
GLfloat vertices1[][3] = { { -0.6,-1.0,-0.05 },{ 0.6,-1.0,-0.05 },{ 0.6,1.0,-0.05 },{ -0.6,1.0,-0.05 },
{ -0.6,-1.0, 0.05 },{ 0.6,-1.0, 0.05 },{ 0.6,1.0, 0.05 },{ -0.6,1.0, 0.05 } };
GLfloat colors1[][4] = { { 0.0, 0.0, 0.0, 0.5 },{ 1.0, 0.0, 0.0, 0.5 },{ 1.0, 1.0, 0.0, 0.5 },{ 0.0, 1.0, 0.0, 0.5 },
{ 0.0, 0.0, 1.0, 0.5 },{ 1.0, 0.0, 1.0, 0.5 },{ 1.0, 1.0, 1.0, 0.5 },{ 0.0, 1.0, 1.0, 0.5 } };
GLubyte texflag[] = { 1,       0,       0,       0,       1,       0 };
GLubyte indices1[] = { 0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4 };

// ---------------------------------------------------------------------------------------------
// Objects
// ---------------------------------------------------------------------------------------------

Object box;
Viewer v;

// ---------------------------------------------------------------------------------------------
// Functions
// ---------------------------------------------------------------------------------------------
void texture_create(Texture* p, int w, int h)
{
	p->rgb = (GLubyte*)malloc(sizeof(GLubyte)*w*h * 3);
	p->width = w;
	p->height = w;
	memset(p->rgb, 0, sizeof(GLubyte)*w*h * 3);
}

void texture_destroy(Texture *p) {
	free(p->rgb);
}

void texture_checkboard(Texture *p, int px, int py)
{
	for (int y = 0; y < p->height; y++)
	{
		for (int x = 0; x < p->width; x++)
		{
			if (((x / px) + (y / px)) % 2)
			{
				p->rgb[(x + y*p->width) * 3 + 0] = 255;
				p->rgb[(x + y*p->width) * 3 + 1] =0;
				p->rgb[(x + y*p->width) * 3 + 2] = 0;

			}
			else {
				p->rgb[(x + y*p->width) * 3 + 0] = 0;
				p->rgb[(x + y*p->width) * 3 + 1] = 0;
				p->rgb[(x + y*p->width) * 3 + 2] = 255;
			}
		}
	}
}

void polygon(Object* p, int index)
{
	static GLfloat texcoord[4][2] = { {0,1},{1,1},{1,0},{0,0} };
	if (texflag[index])
	{
		glEnable(GL_TEXTURE_2D); glBegin(GL_POLYGON);
		for (int i = 0; i < 4; i++)
		{
			glColor4f(1, 1, 1, 0);
			glTexCoord2fv(texcoord[i]);
			glVertex3fv(&p->vertices[p->indices[index * 4 + i] * 3]);
		}
		glEnd();
	}
	else
	{
		glDisable(GL_TEXTURE_2D); glBegin(GL_POLYGON);
		for (int i = 0; i < 4; i++)
		{
			glColor4fv(&p->colors[p->indices[index * 4 + i] * 4]);
			glVertex3fv(&p->vertices[p->indices[index * 4 + i] * 3]);
		}
		glEnd();
	}
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-1.5, 1.5, -1.5, 1.5, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);

	Texture tex;
	texture_create(&tex, 512, 512);
	texture_checkboard(&tex, 32, 32);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex.width, tex.height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex.rgb);
	//미리 밉맵에대해서 여러크기의 미리 만들어낸 이미지가 있어 여기에 쓰는 맵핑방식을 쓸 수 가 있는데, 0 이ㅏ는건 원본을 쓰겠다.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//이미지(텍스트) 배경화면보다 작으면, 늘릴건지 반복할 건지, 옵션 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

}

void spin()
{
	glutPostRedisplay();
}

//void polygon(Object* p, int index)
//{
//	glBegin(GL_POLYGON);
//	for (int i = 0; i<4; i++)
//	{
//		glColor4fv(&p->colors[p->indices[index * 4 + i] * 4]);
//		glVertex3fv(&p->vertices[p->indices[index * 4 + i] * 3]);
//	}
//	glEnd();
//}

void cube(Object* p)
{
	for (int i = 0; i<6; i++)
	{
		polygon(p, i);
	}
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

void draw(Object* p)
{
	// store matrix
	glPushMatrix();

	// transformation
	glTranslatef(p->trans[0], p->trans[1], p->trans[2]);
	glRotatef(p->theta[0], 1.0, 0.0, 0.0);
	glRotatef(p->theta[1], 0.0, 1.0, 0.0);
	glRotatef(p->theta[2], 0.0, 0.0, 1.0);

	// draw myself
	cube(p);

	// draw children
	if (p->child) draw(p->child);

	// restore matrix
	glPopMatrix();

	// draw siblings
	if (p->next) draw(p->next);
}

void display()
{
	// clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// setup viewer
	glLoadIdentity();
	gluLookAt(v.eye[0], v.eye[1], v.eye[2], v.at[0], v.at[1], v.at[2], v.up[0], v.up[1], v.up[2]);

	// draw
	draw(&box);

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
	glutCreateWindow("Prog31");

	// call-back functions
	glutIdleFunc(spin);
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	// object initialization
	box.vertices = &vertices1[0][0];
	box.colors = &colors1[0][0];
	box.indices = &indices1[0];
	box.nums = 24;

	box.theta[0] = box.theta[1] = box.theta[2] = 0;
	box.trans[0] = box.trans[1] = box.trans[2] = 0;
	box.next = 0;
	box.child = 0;

	// initialize viewer
	v.eye[0] = 1.0; v.eye[1] = 1.0; v.eye[2] = 1.0;
	v.at[0] = 0.0; v.at[1] = 0.0; v.at[2] = 0.0;
	v.up[0] = 0.0; v.up[1] = 1.0; v.up[2] = 0.0;

	init();
	glutMainLoop();

	return 0;
}
