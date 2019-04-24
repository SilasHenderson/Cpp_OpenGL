// ------ Drawing Robot-3d {Silas Henderson} ------
#include <GL/freeglut.h>
#include <cmath>
#include <cstdio>
#include <iostream>

// ------------------------- Vars--------------------------------
int   	canvas, ax, 	topBar, sideBar;
double 	ang0, 	ang1,	ang2, 	r;
double 	n1x, 	n1y, 	n1z; 
double 	n2x,	n2y, 	n2z; 

char 	buffer[40];
double 	drawing[3][2000];

double L1  =  1;	int	addPoints  = 1;	
double L2  =  1;	int mouseClick = 0;
double h   = .5;	int mouseDown  = 0;  int drawingPointsCount = 0;

double 	el  = .5, az  = .5, mx  = 0, my  = 0, loopCount = 0;
double 	el0 =  0, az0 = .5, mx0 = 0, my0 = 0, axSize    = 3;

// ---------------------------------- Solver ---------------------------
void angFind(double x, double y, double z) {
r    =    sqrt(x*x + y*y);
ang0 = -2*atan((x - r)/y);
ang1 =  2*atan((2*L1*z - sqrt(- L1*L1*L1*L1 + 2*L1*L1*L2*L2 + 2*L1*L1*r*r + 2*L1*L1*z*z 
	                          - L2*L2*L2*L2 + 2*L2*L2*r *r  + 2*L2*L2*z*z 
	                          - r *r *r * r - 2*r *r *z *z  - z*z*z*z))
               /(L1*L1 + 2*L1*r - L2*L2 + r*r + z*z));

ang2 = 2*atan((2*L2*z + sqrt((- L1*L1 + 2*L1*L2 - L2*L2 + r*r + z*z)
	                        *(  L1*L1 + 2*L1*L2 + L2*L2 - r*r - z*z)))
               /(- L1*L1 + L2*L2 + 2*L2*r + r*r + z*z));}

// ---------------------------------- Draw Arm --------------------------
void drawArm() {
	glColor3f(.2, .2, .2);			glLineWidth(4);
	n1x = cos(ang0)*L1*cos(ang1); 	n2x = cos(ang0)*(L1*cos(ang1) + L2*cos(ang2));
	n1y = sin(ang0)*L1*cos(ang1); 	n2y = sin(ang0)*(L1*cos(ang1) + L2*cos(ang2));
	n1z = L1*sin(ang1);				n2z = L1*sin(ang1) + L2*sin(ang2);

	if (addPoints == 1) {
		drawing[0][drawingPointsCount] = n2x;
		drawing[1][drawingPointsCount] = n2y;
		drawing[2][drawingPointsCount] = n2z;	drawingPointsCount = drawingPointsCount + 1;}

	glPointSize(3);		glColor3f(.1, .3, .1);	glBegin(GL_POINTS);
	for (int i = 0; i < drawingPointsCount; i++) {
		glVertex3d(drawing[0][i], drawing[1][i], drawing[2][i]);}	glEnd();
		
	glColor3f(.2, .2, .2);		glBegin(GL_LINE_STRIP);
	glVertex3d(0, 0,  0);   	glVertex3d(n1x, n1y, n1z);	glVertex3d(n2x, n2y, n2z);	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3d(0,       (-L1 - L2)/2, 0);	glVertex3d(0,       ( L1 + L2)/2, 0);
	glVertex3d(L1 + L2, ( L1 + L2)/2, 0);	glVertex3d(L1 + L2, (-L1 - L2)/2, 0);
	glVertex3d(0,       (-L1 - L2)/2, 0);	glEnd();}

// ------------------------------- Mouse --------------------------
	void mouse () {
		if (mx < 500 && my > 50) {
			if (mouseClick == 1) {mx0 = mx; my0 = my; 
								  el0 = el; az0 = az; mouseClick = 0;}
			if (mouseDown == 1)  {az  = az0 + (mx - mx0)/200;
			                      el = el0 + (my - my0)/200;}}
		
		if (my < 50 && mouseDown == 1) {
			if (mx > 0    && mx < 40)  axSize 	= axSize + .1;
			if (mx > 50   && mx < 90)  axSize 	= axSize - .1;
			if (mx > 100  && mx < 140) L1 	  	= L1 + .005;
			if (mx > 150  && mx < 190) L1 		= L1 - .005;	}}

	void mouseClickCall(int key, int state, int x, int y) {
		if (state == GLUT_DOWN) { mouseDown = 1; mouseClick = 1;}
		if (state == GLUT_UP)   { mouseDown = 0;				}}

	void mouseMoveUpCall(    	int x, int y) 	{ mx = x;	   	my = y + 50;}
	void mouseMoveUpCallSide(	int x, int y) 	{ mx = x + 500; my = y + 50;}
	void mouseMoveUpCallTop( 	int x, int y) 	{ mx = x; 		my = y;		}

	void mouseMoveDownCall(    	int x, int y) 	{ mx = x;		my = y + 50;}
	void mouseMoveDownCallSide(	int x, int y)	{ mx = x + 500;	my = y + 50;}
	void mouseMoveDownCallTop(	int x, int y) 	{ mx = x; 		my = y;		}

// -------------------------------- Loop -----------------------------
void loop(int) {
	loopCount++;	mouse();
	glutSetWindow(ax); 
		glClearColor(.7, .7, .7, 1);	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();			
		gluLookAt(0, 0, 0, 12*cos(el)*cos(az), 12*cos(el)*sin(az), 12*sin(el), 0, 0, 1);
		
		glOrtho(-axSize, axSize, -axSize, axSize, -axSize, axSize);
		angFind(.5 + cos(loopCount/40), .3 + sin(loopCount/40), 0);
		drawArm();
		glutSwapBuffers();

	glutSetWindow(topBar);
		glClearColor(.1, .12, .15, 1);	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glColor3f(.8, .9, .9);

		sprintf(buffer, "z-"); 	glRasterPos2f(-.95, -.2);	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*) buffer);
		sprintf(buffer, "z+"); 	glRasterPos2f(-.8,  -.2);	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*) buffer);
		sprintf(buffer, "L1-"); glRasterPos2f(-.65, -.2);	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*) buffer);
		sprintf(buffer, "L1+"); glRasterPos2f(-.5,  -.2);	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*) buffer);
		sprintf(buffer, "L2-"); glRasterPos2f(-.35, -.2);	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*) buffer);
		sprintf(buffer, "L2+"); glRasterPos2f(-.2,  -.2);	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*) buffer);

		sprintf(buffer, "ang0 = %3.2f", ang0);	glRasterPos2f( .6,  .5);	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)buffer);
		sprintf(buffer, "ang1 = %3.2f", ang1);  glRasterPos2f( .6, -.1); 	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)buffer);
		sprintf(buffer, "ang2 = %3.2f", ang2);  glRasterPos2f( .6,-.7); 	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)buffer);

		sprintf(buffer, "mx = %3.2f", mx); 		glRasterPos2f(.2, .5); 		glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)buffer);
		sprintf(buffer, "my = %3.2f", my);		glRasterPos2f(.2, -.1);		glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)buffer);
		glutSwapBuffers();

	glutSetWindow(sideBar);
		glClearColor(.01, .01, .01, 1);	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glColor3f(.5,  .52, .53); 		glRectf(-1, -1, 1, -.63);
		glColor3f(.52, .5,  .4);	 	glRectf(-1,-.6, 1, -.23);
		glColor3f(.4,  .5,  .3); 		glRectf(-1,-.2, 1,  .17);
		glColor3f(.4,  .4,  .4); 		glRectf(-1, .2, 1,  .57);
		glColor3f(.5,  .5,  .5); 		glRectf(-1, .6 , 1,   1);
     	glutSwapBuffers();

	glutTimerFunc(10, loop, 0); }

// ---------------------------------- Setup ----------------------------
int main(int argc, char** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(600, 500);
	
	canvas  = glutCreateWindow("taco-time");
	
	topBar  = glutCreateSubWindow(canvas,   0,   0, 600,  50);
		glutMotionFunc(mouseMoveDownCallTop);
		glutPassiveMotionFunc(mouseMoveUpCallTop);
		glutMouseFunc(mouseClickCall);
	
	sideBar = glutCreateSubWindow(canvas, 500,  60,  90, 430);
		glutMotionFunc(mouseMoveDownCallSide);
		glutPassiveMotionFunc(mouseMoveUpCallSide);
		glutMouseFunc(mouseClickCall);

	ax      = glutCreateSubWindow(canvas,  10,  60, 480, 430);
		glutMotionFunc(mouseMoveDownCall);
		glutPassiveMotionFunc(mouseMoveUpCall);
		glutMouseFunc(mouseClickCall);
		glClearColor(.1, .1, .1, 1);
		glEnable(GL_DEPTH_TEST);

	glutTimerFunc(10, loop, 0);
	glutMainLoop();}
