// ------ Drawing Robot-3d {Silas Henderson} ------
#include <GL/freeglut.h>
#include <cmath>
#include <cstdio>

// ------------------------- Vars--------------------------------
double L1  =  1;
double L2  =  1;	
double h   = .5;

int mouseClick = 0; 	double camDist = 5;
int mouseDown  = 0; 	int pause      = 0;	int showPathTarget = 1;	

int   	canvas, ax, 	topBar, sideBar;	char 	buffer[40];
double 	ang0, 	ang1,	ang2, 	r;			double 	drawing[3][5000];
double 	n1x, 	n1y, 	n1z; 				double 	target[3][5000];			
double 	n2x, 	n2y, 	n2z; 				double  path[3][500];

int pathTotalPt   = 0; 	int targetTotalPt = 0;	
int pathPt        = 0;	int targetPt      = 0;	double paperSize = L1 + L2;
int followPath    = 0; 	int followTarget  = 0;	int drawingPointsCount = 0;

double 	el  = .67, 	az  = -.6, 	mx  = 0,	my  = 0; 	
double 	el0 =   0, 	az0 =   0,  mx0 = 0, 	my0 = 0;

double bgColor[] = {.15, .15, .15, 1};

int draw3d = 0;

// ---------------------------------- Solver ---------------------------
void angFind(double x, double y, double z) {
	z    = z - h;	
	r    =    sqrt(x*x + y*y);
	ang0 = -2*atan((x - r)/y);
	ang1 =  2*atan((2*L1*z + sqrt(- L1*L1*L1*L1 + 2*L1*L1*L2*L2 + 2*L1*L1*r*r + 2*L1*L1*z*z 
		                          - L2*L2*L2*L2 + 2*L2*L2*r *r  + 2*L2*L2*z*z 
	    	                      - r *r *r * r - 2*r *r *z *z  - z*z*z*z))
            	   /(L1*L1 + 2*L1*r - L2*L2 + r*r + z*z));

	ang2 = 2*atan((2*L2*z - sqrt((- L1*L1 + 2*L1*L2 - L2*L2 + r*r + z*z)
		                        *(  L1*L1 + 2*L1*L2 + L2*L2 - r*r - z*z)))
        	       /(- L1*L1 + L2*L2 + 2*L2*r + r*r + z*z));}

// ---------------------------------- Shapes ---------------------------
void pathGen() {
	double x0 = n2x;	double x1 = target[0][targetPt];
	double y0 = n2y;	double y1 = target[1][targetPt];
	double z0 = n2z;	double z1 = target[2][targetPt];

	if (draw3d == 0) {
		pathPt = 0;		pathTotalPt = -1;
		for (int i = 0; i < 31; i++) {
			pathTotalPt++;
			path[0][pathTotalPt] = x0;
			path[1][pathTotalPt] = y0;
			path[2][pathTotalPt] = z0 + double(i)/30*(.5);}

		for (int i = 0; i < 61; i++) {
			pathTotalPt++;
			path[0][pathTotalPt] = x0 + double(i)/60*(x1 - x0);
			path[1][pathTotalPt] = y0 + double(i)/60*(y1 - y0);
			path[2][pathTotalPt] = .5;}

		for (int i = 0; i < 31; i++) {
			pathTotalPt++;
			path[0][pathTotalPt] = x1;
			path[1][pathTotalPt] = y1;
			path[2][pathTotalPt] = .5 - double(i)/30*(.5);}}

	if (draw3d == 1){
		pathPt = 0; pathTotalPt = 0;
		for (int i = 0; i < 81; i++) {
			path[0][pathTotalPt] = x0 + double(i)/80*(x1 - x0);
			path[1][pathTotalPt] = y0 + double(i)/80*(y1 - y0);
			path[2][pathTotalPt] = z0 + double(i)/80*(z1 - z0);
			pathTotalPt++;}}}

void flowerGen(double radius, double x, double y) {
	for (int i = 0; i < 360; i++) {
		double ang = double(i)/360*6.28 + .01;
		target[0][targetTotalPt] = radius*cos(ang*2)*cos(ang) + x;
		target[1][targetTotalPt] = radius*cos(ang*2)*sin(ang) + y;
		target[2][targetTotalPt] = 0;
		targetTotalPt++;}}

void circleGen(double radius, double x, double y) {
	for (int i = 0; i < 360; i++) {
		double ang = double(i)/360*6.28;
		target[0][targetTotalPt] = radius*cos(ang) + x;
		target[1][targetTotalPt] = radius*sin(ang) + y;
		target[2][targetTotalPt] = 0;
		targetTotalPt++;}}

void spiralGen(double radius, double x, double y) {
	for (int i = 0; i < 360; i++) {
		double ang = double(i)/360*6.29;
		target[0][targetTotalPt] = radius*cos(2*ang) + x;
		target[1][targetTotalPt] = radius*sin(2*ang) + y;
		target[2][targetTotalPt] = ang/6.29;
		targetTotalPt++;}}

void refresh3d() {targetTotalPt      = 0;	targetPt     = 0;	showPathTarget = 0;
				  pathTotalPt        = 0; 	pathPt       = 0; 	draw3d = 1;
				  drawingPointsCount = 0; 	followTarget = 1;
				  spiralGen(.4, .5, .5);}

void refresh2d() {targetTotalPt      = 0;	targetPt     = 0;	showPathTarget = 0;
				  pathTotalPt        = 0; 	pathPt       = 0; 	draw3d = 0;
				  drawingPointsCount = 0; 	followTarget = 1;		
				  flowerGen(.4, .5, .5); 	circleGen(.4, .5, -.5);
				  flowerGen(.2, .8, .8);	circleGen(.8, .4,  .4);}

// ---------------------------------- Draw Arm --------------------------
void drawArm() {
	glColor3f(.2, .2, .2);			glLineWidth(4);
	n1x = cos(ang0)*L1*cos(ang1); 	n2x = cos(ang0)*(L1*cos(ang1) + L2*cos(ang2));
	n1y = sin(ang0)*L1*cos(ang1); 	n2y = sin(ang0)*(L1*cos(ang1) + L2*cos(ang2));
	n1z = h + L1*sin(ang1);			n2z = h + L1*sin(ang1) + L2*sin(ang2);

	if (followTarget == 1) {
		drawing[0][drawingPointsCount] = n2x;
		drawing[1][drawingPointsCount] = n2y;
		drawing[2][drawingPointsCount] = n2z;	drawingPointsCount = drawingPointsCount + 1;}

	glPointSize(3);		glColor3f(.1, .3, .1);	glBegin(GL_POINTS);
	for (int i = 0; i < drawingPointsCount; i++) {
		glVertex3d(drawing[0][i], drawing[1][i], drawing[2][i]);}	glEnd();

	glColor3f(.2, .2, .2);					glBegin(GL_LINE_STRIP);
	glVertex3d(0,  0,  0);
	glVertex3d(0,  0,  h);
	glVertex3d(n1x, n1y, n1z);
	glVertex3d(n2x, n2y, n2z);				glEnd();

	//--------------------------- reference lines ---------------------- //
	glColor4f(.3, .1, .3, .2);	glLineWidth(1);					glBegin(GL_LINES);
	glVertex3d(n1x, n1y, n1z);
	glVertex3d(n1x + L2/2*cos(ang0)*cos(ang1 - 1.57), 
			   n1y + L2/2*sin(ang0)*cos(ang1 - 1.57),
	           n1z + L2/2*sin(ang1 - 1.57));						glEnd();

	// ---------------------------- 
	glColor4f(.2, .4, .2, .5);	glLineWidth(1);  				glBegin(GL_LINES);			
	
	// node 1 floor projection
	glVertex3d(0,     0,  0);	glVertex3d(n1x,   0,    0);
	glVertex3d(0,     0,  0);	glVertex3d(  0, n1y,    0);
	glVertex3d(n1x,   0,  0);	glVertex3d(n1x, n1y,    0);
	glVertex3d(0,   n1y,  0);	glVertex3d(n1x, n1y,    0); 

	// node 1 raised floor projection	
	glVertex3d(0,     0,  h);	glVertex3d(n1x,   0,    h);
	glVertex3d(0,     0,  h);	glVertex3d(  0, n1y,    h);
	glVertex3d(n1x,   0,  h);	glVertex3d(n1x, n1y,    h);
	glVertex3d(0,   n1y,  h);	glVertex3d(n1x, n1y,    h); 	

	// node 1 ground to h0 stilts
	glVertex3d(0,     0,  0);	glVertex3d(  0,   0,    h);
	glVertex3d(n1x,   0,  0);	glVertex3d(n1x,   0,    h);
	glVertex3d(0,   n1y,  0);	glVertex3d(  0, n1y,    h); 	
	glVertex3d(n1x, n1y,  0);	glVertex3d(n1x, n1y,    h);		glEnd();

	// node 1 special triangle
	glLineWidth(2);		glColor3f(.3, .1, .1); 					glBegin(GL_LINES);
	glVertex3d(0,  0,  h);		glVertex3d(n1x, n1y,    h);
	glVertex3d(n1x, n1y, h);	glVertex3d(n1x, n1y, n1z);

	glEnd();


	glColor3f(.2, .2, .2); glLineWidth(3);	glBegin(GL_LINE_STRIP);
	glVertex3d(0, 		 -paperSize/2, 0);	glVertex3d(paperSize*.9,  -paperSize/2, 0);	
	glVertex3d(paperSize*.9, paperSize/2, 0);	glVertex3d(0,			paperSize/2, 0);
	glVertex3d(0, 		 -paperSize/2, 0);	glEnd();

	if (showPathTarget == 1) {
		glPointSize(1.5);
		glColor4f(.6, .3, .3, 0);	glBegin(GL_POINTS);	
		for (int i = 0; i < pathTotalPt;   i++) {
			glVertex3d(  path[0][i],   path[1][i],   path[2][i]);}
			glEnd();

		glColor4f(.3, .3, .6, 0);	glBegin(GL_POINTS);
		for (int i = 0; i < targetTotalPt; i++) {
			glVertex3d(target[0][i], target[1][i], target[2][i]);}
		glEnd();}}

// ------------------------------- Mouse --------------------------
	void mouse () {
		if (mouseDown == 1) bgColor[0] =  .2; bgColor[1] = .15;  bgColor[2] = .15;
		if (mouseDown == 0) bgColor[0] = .15; bgColor[1] = .15;  bgColor[2] = .15;

		if (mx < 500 && my > 50) {
			if (mouseClick == 1) {mx0 = mx; my0 = my; 
								  el0 = el; az0 = az;}
			if (mouseDown == 1)  {az  = az0 - (mx - mx0)/500;
			                      el  = el0 + (my - my0)/500;}
			if (el < -.5) el = -.5;
			if (el >  1)  el =   1;}

		if (mx > 500 && mouseClick == 1) {
			if (my > 50 &&  my < 140) { refresh2d();}
			if (my > 140 && my < 225) { if  (showPathTarget == 1) showPathTarget = 0;
										else showPathTarget = 1;}
			if (my > 225 && my < 300) { if  (pause == 0) pause = 1;
										else pause = 0;}
			if (my > 310 && my < 400) { refresh3d();}
			if (my > 400) drawingPointsCount = 0;}           

		if (my < 50 && mouseDown == 1) {
			if (mx > 0    && mx < 40)  camDist += .04;
			if (mx > 50   && mx < 90)  camDist -= .04;
			if (mx > 100  && mx < 140) L1 	  	= L1 - .01;
			if (mx > 145  && mx < 185) L1 		= L1 + .01;
			if (mx > 190  && mx < 230) L2 		= L2 - .01;	
			if (mx > 235  && mx < 270) L2       = L2 + .01;}

		mouseClick = 0;}

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

	mouse();

	if (pause == 0) {
		if (followPath == 0 && followTarget == 0) {refresh2d();}
		if (followTarget == 1) {
			angFind(target[0][targetPt], target[1][targetPt], target[2][targetPt]);	targetPt++;
			double dist = abs(target[0][targetPt] - n2x)
					   	+ abs(target[1][targetPt] - n2y)
						+ abs(target[2][targetPt] - n2z);
			if (dist > .1 ) { pathGen();	followPath = 1; followTarget = 0;}}
		
		if (followPath == 1) {
			angFind(path[0][pathPt], path[1][pathPt], path[2][pathPt]);		pathPt++;
			if (pathPt > pathTotalPt - 1) { followTarget = 1;  followPath = 0;}}}
	
	glutSetWindow(canvas); 				
	glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();

	glutSetWindow(ax); 
		glClearColor(.7, .7, .7, 1);	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW); 	glLoadIdentity();
		gluLookAt(camDist*cos(el)*cos(az) + .6, 
			      camDist*cos(el)*sin(az) + .3,
		    	  camDist*sin(el) - .2, 
		    	  .6, .3, -.2, 0, 0, 1);
		drawArm();	

		glMatrixMode(GL_PROJECTION);	glLoadIdentity();	gluPerspective(40, 1, .1, 100);
		glutSwapBuffers();
		glFlush();
		
	glutSetWindow(topBar);
		glClearColor(.1, .1, .1, 1);	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glColor3f(.7, .7, .9);	sprintf(buffer, "z-"); 	glRasterPos2f(-.95, -.2);	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*) buffer);
		glColor3f(.9, .9, .9);	sprintf(buffer, "z+"); 	glRasterPos2f(-.8,  -.2);	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*) buffer);
		glColor3f(.7, .7, .9);	sprintf(buffer, "L1-"); glRasterPos2f(-.65, -.2); 	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*) buffer);
		glColor3f(.9, .9, .9);	sprintf(buffer, "L1+"); glRasterPos2f(-.5,  -.2);	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*) buffer);
		glColor3f(.7, .7, .9);	sprintf(buffer, "L2-"); glRasterPos2f(-.35, -.2);	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*) buffer);
		glColor3f(.9, .9, .9);	sprintf(buffer, "L2+"); glRasterPos2f(-.2,  -.2);	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*) buffer);

		glColor3f(.7, .7, .65);
		float ang0Star = 90 - ang0*180/3.14;
		float ang1Star = 180 - ang1*180/3.14;
		float ang2Star = 180 + (ang2 - ang1)*180/3.14;

		sprintf(buffer, "ang0 = %4.1f", ang0Star);	glRasterPos2f(.55,  .45);	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)buffer);
		sprintf(buffer, "ang1 = %4.1f", ang1Star);  glRasterPos2f(.55, -.15); 	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)buffer);
		sprintf(buffer, "ang2 = %4.1f", ang2Star);  glRasterPos2f(.55, -.75); 	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)buffer);

		glColor3f(.7, .65, .7);	double zStar = n2z;
		if (n2z > -.01 && n2z < .01) zStar = 0;
		sprintf(buffer, "x = %3.1f", n2x);	glRasterPos2f(.25,  .45);	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)buffer);
		sprintf(buffer, "y = %3.1f", n2y); 	glRasterPos2f(.25, -.15); 	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)buffer);
		sprintf(buffer, "z = %3.1f", zStar);glRasterPos2f(.25, -.75); 	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)buffer);

		glColor3f(.65, .7, .7);
		sprintf(buffer, "L1 = %2.1f", L1);	glRasterPos2f(0,  .45);		glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)buffer);
		sprintf(buffer, "L2 = %2.1f", L2); 	glRasterPos2f(0, -.15); 	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)buffer);
		sprintf(buffer, "h =  %2.1f", h); 	glRasterPos2f(0, -.75); 	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)buffer);

		glutSwapBuffers();

	glutSetWindow(sideBar);
		glClearColor(.01, .01, .01, 1);	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glColor4f(.5,  .52, .53, 0); 		glRectf(-1,  -1,  1, -.63);
		glColor4f(.52, .5,  .4,  0);	 	glRectf(-1, -.6,  1, -.23);
		glColor4f(.4,  .5,  .3,  0); 		glRectf(-1, -.2,  1,  .17);
		glColor4f(.4,  .4,  .4,  0); 		glRectf(-1,  .2,  1,  .57);
		glColor4f(.5,  .5,  .5,  0); 		glRectf(-1, .6 ,  1,    1);  	

		glColor4f(.1, .05, .05, 1);

		sprintf(buffer, "New");     glRasterPos2f( -.5, .75); 	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)buffer);
		sprintf(buffer, "Path");    glRasterPos2f( -.5, .35); 	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)buffer);
		sprintf(buffer, "Pause");   glRasterPos2f(-.65,-.06); 	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)buffer);
		sprintf(buffer, "3d"); 		glRasterPos2f(-.25,-.45);	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)buffer);
		sprintf(buffer, "Clear");	glRasterPos2f(-.65, -.83);	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)buffer);

		glutSwapBuffers();

	glutTimerFunc(15, loop, 0); }

// ---------------------------------- Setup ----------------------------
int main(int argc, char** argv) {

	n2x = 1; 	n2y = -.5; n2z = 0;
	angFind(n2x, n2y, n2z);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(600, 500);
	
	canvas  = glutCreateWindow("");
	
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

	glutTimerFunc(15, loop, 0);
	glutMainLoop();}