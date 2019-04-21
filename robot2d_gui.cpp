#include <GL/freeglut.h>
#include <cstdio>
#include <cmath>

int canvas, ax0, ax1;
char buffer[20];
int mouseDown = 1;

int key[5] = {0, 0, 0, 0, 0};

int demoRun = 0;

double ang[2] = {0, 0};

int countDown = 100;


double loopCount = 0;

// -------------------------------- Mouse -------------------------------
void mouse() {
	if (key[0] == 1) {ang[0] = ang[0] + .02;}
	if (key[1] == 1) {ang[0] = ang[0] - .02;}
	if (key[2] == 1) {ang[1] = ang[1] + .02;}
	if (key[3] == 1) {ang[1] = ang[1] - .02;}
	if (key[4] == 1) {demoRun = 1;}}

void mouseClick(int button, int state, int x, int y){
	if (y < 50) {
		if (state == GLUT_DOWN) {
			if (x > 200 && x < 300) {key[4] = 1;}
			if (x > 300 && x < 350) {key[0] = 1;}
			if (x > 350 && x < 400) {key[1] = 1;}
			if (x > 400 && x < 450) {key[2] = 1;}
			if (x > 450 && x < 500) {key[3] = 1;}}
		if (state == GLUT_UP) {
			key[0] = 0; key[1] = 0; key[2] = 0; key[3] = 0; key[4] = 0;}}}

void renderAx0() {
	glutSetWindow(ax0);  	
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor4f(.9, .9, .9, 1);

	sprintf(buffer, "ang0 = %.2f", ang[0]);
	glRasterPos2f(-.9, .3);	
	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)buffer);

	sprintf(buffer, "ang1 = %.2f", ang[1]);
	glRasterPos2f(-.9, -.5);
	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)buffer);

	glRasterPos2f( .2, 0);  glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)"left");
	glRasterPos2f( .4, 0);	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)"right");	
	glRasterPos2f( .6, 0);	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)"fwd");
	glRasterPos2f( .8, 0);  glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)"back");

	glutSwapBuffers();}

void renderAx1() {
	glutSetWindow(ax1);		
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(cos(ang[0]), sin(ang[0]));
	glVertex2f(cos(ang[0]) + cos(ang[1]), sin(ang[0]) + sin(ang[1]));
	glEnd();

	glutSwapBuffers(); }

// --------------------------- Loop -------------------------------
void loop(int) {
	
	mouse();
	renderAx0();
	renderAx1();

	if (demoRun == 1) {
		countDown = countDown - 1;

		ang[0] = ang[0] + .1;
		ang[1] = ang[1] - .1;

		if (countDown < 1) {demoRun = 0; countDown = 100;}}

	glutTimerFunc(10, loop, 0);}

// -------------------------------------- Main -------------------------
int main(int argc, char**argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(500, 500);

	glutMouseFunc(mouseClick);

	canvas = glutCreateWindow("bananas");

	ax0    = glutCreateSubWindow(canvas, 0,   0, 500,  50);
		glClearColor(.1, .15, .2, 1);
		glutMouseFunc(mouseClick);

	ax1    = glutCreateSubWindow(canvas, 10, 60, 480, 430);
		glClearColor(.1, .1, .1, 1);
		glutMouseFunc(mouseClick);
		glutTimerFunc(10, loop, 0);
	
	glutMainLoop();}