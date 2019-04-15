#include <iostream>
#include <chrono>
#include <GL/glut.h>
#include <math.h>

double L1 = 1; 	double currentX;
double L2 = 1;  double currentY;

int ptNum = 0;
int shape = 0;

int drawingOn = 1;
double drawing[2][2000];

// ---------------------------- pause function ----------------------
void pause(double DT) {
	int pauseOn = 1;
	auto     t0 = std::chrono::system_clock::now();
	while (pauseOn == 1) {
		auto t1 = std::chrono::system_clock::now();
		std::chrono::duration<double> dt = t1 - t0;
		if (dt.count() > DT) {pauseOn =0;}}}

// ------------------------- Math -----------------------------------
void drawPoint(double x, double y) {

	double ang0 = 2*atan((2*L1*y - 
    	sqrt( -   L1*L1*L1*L1 + 2*L1*L1*L2*L2 -   L2*L2*L2*L2 
              + 2*L1*L1* x* x + 2*L1*L1* y* y + 2*L2*L2* x* x 
              + 2*L2*L2* y* y -    x* x* x* x - 2* x* x* y* y - y* y* y* y))
        /(L1*L1 + 2*L1*x - L2*L2 + x*x + y*y));

    	double ang1 = 2*atan((2*L2*y + 
       		  sqrt((- L1*L1 + 2*L1*L2 - L2*L2 + x*x + y*y)
          	      *(  L1*L1 + 2*L1*L2 + L2*L2 - x*x - y*y)))     
           	      /(- L1*L1 + 2*L2*x  + L2*L2 + x*x + y*y));

    double n0x = 0;	double n1x = L1*cos(ang0); double n2x = n1x + L2*cos(ang1);
    double n0y = 0;	double n1y = L1*sin(ang0); double n2y = n1y + L2*sin(ang1);
    	   	
    glBegin(GL_LINE_STRIP); 	glVertex2d(n0x, n0y);
    			 	glVertex2d(n1x, n1y);
    				glVertex2d(n2x, n2y);    		glEnd();
   if (drawingOn == 1) {
   	drawing[0][ptNum] = n2x;
    	drawing[1][ptNum] = n2y;   	ptNum = ptNum + 1; 
    	
    	glBegin(GL_POINTS);
    	for (int i = 0; i < ptNum; i++) {
    		glVertex2d(drawing[0][i], drawing[1][i]);}; 	glEnd();}

	glutSwapBuffers();	pause(.005);	glClear(GL_COLOR_BUFFER_BIT);}

void drawShape(int shape, double radius, double cx, double cy) {
	double x; double y;
	drawingOn = 1;
	if (shape == 0) {
		for (double i = 0; i < 6.28; i = i + .1){
			x = .5 + .3*cos(i);
			y = .5 + .3*sin(i);
			drawPoint(x, y);}}

	if (shape == 1) {
		for (double i = 0; i < 6.28; i = i + .01){
			x = -.5 + cos(2*i)*cos(i);
			y = -.5 + cos(2*i)*sin(i);
			drawPoint(x, y);}}
	if (shape == 2) {
		for (double i = 0; i < 6.28; i = i + .01) {
			x = cx + i/6.26*radius*cos(i);
			y = cy + i/6.26*radius*sin(i);}}}

void moveArm(double numPoints, double p1x, double p1y, double p2x, double p2y) {
	
	double x, y;
	drawingOn = 0;
	for (double i = 0; i < numPoints; i++) {

		x = p1x + (p2x - p1x)*i/numPoints;
		y = p1y + (p2y - p1y)*i/numPoints;

		drawPoint(x, y);}}

void drawLoop() {
	drawShape(0, .3, -.5,  -.5);	moveArm(40, .5, .5, 0, 0);
	drawShape(1, .3,  .5,  -.5);
	drawShape(2, .3, -.5,   .5);
	drawShape(0, .3,  .5,   .5);}

//  --------------------------- init/main -----------------------------
int main(int argc, char** argv) {  

	// Init
	glutInit(&argc, argv);                                         
   	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutCreateWindow("crowTRobot");

 	// Functions
    	glutDisplayFunc(drawLoop);
    	glutMainLoop();}
