// HW4.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include <glut.h>
#include "ImageProc.h"

// ---------------------------------------------------------------------------------------------
// Globals
// ---------------------------------------------------------------------------------------------

ImageProc g_cImg;
int       g_qunt_step = 1;

// ---------------------------------------------------------------------------------------------
// Initialize & Idle
// ---------------------------------------------------------------------------------------------

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle()
{
	glutPostRedisplay();
}

// ---------------------------------------------------------------------------------------------
// I/O
// ---------------------------------------------------------------------------------------------

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'g') g_cImg.convertToGray();
	if (key == 'p') g_cImg.convertToSepia();
	if (key == 's') g_cImg.samplingBy2();
	if (key == 'q') { g_qunt_step *= 2; g_cImg.quantization(g_qunt_step); }
	if (key == 'o') { g_qunt_step = 1; g_cImg.loadFromBMP("input.bmp"); }
	if (key == 'k') g_cImg.kuwahara();
}

// ---------------------------------------------------------------------------------------------
// Display
// ---------------------------------------------------------------------------------------------

void display()
{
	// clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw background
	glLoadIdentity();
	glRasterPos3f(-2.0, -2.0, -8.0);

	glPixelZoom((GLfloat)glutGet(GLUT_WINDOW_WIDTH) / g_cImg.getWidth(), (GLfloat)glutGet(GLUT_WINDOW_HEIGHT) / g_cImg.getHeight());
	glDrawPixels(g_cImg.getWidth(), g_cImg.getHeight(), GL_RGB, GL_UNSIGNED_BYTE, g_cImg.getRGB());

	// flush & swap buffers
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{

	// load background
	g_cImg.loadFromBMP("input.bmp");

	// GLUT initialization
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(g_cImg.getWidth(), g_cImg.getHeight());
	glutCreateWindow("HW4");

	// call-back functions
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	// texture initialization
	glEnable(GL_TEXTURE_2D);

	// initialize & run
	init();
	glutMainLoop();

	return 0;
}
