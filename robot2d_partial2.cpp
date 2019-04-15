#include <iostream>
#include <chrono>
#include <GL/glut.h>
#include <math.h>

double L1 = 1; 		double ang0;	
double L2 = 1;  	double ang1;

double n0x = 0; 	double n1x, n2x;		
double n1x = 0; 	double n1y, n2y; 

double target[2][100];
double drawing[2][2000];

// --------------------------- Pause Function ----------------------------
void pause(double DT) {      glutSwapBuffers();	
	auto t0 = std::chrono::system_clock::now();
	
	while (1) {	
		auto t1 = std::chrono::system_clock::now();
		std::chrono::duration<double> dt = t1 - t0;
		
		if (dt.count() > DT) {break;}}

	glClear(GL_COLOR_BUFFER_BIT);}

// -------------------------- Angle/Node Solver ---------------------------
void angNodeSolve(double tx, double ty) { 
    ang0 = 2*atan((2*L1*y - 														// Find Ang0
    	sqrt( -   L1*L1*L1*L1 + 2*L1*L1*L2*L2 -   L2*L2*L2*L2 
          	  + 2*L1*L1* x* x + 2*L1*L1* y* y + 2*L2*L2* x* x 
           	  + 2*L2*L2* y* y -    x* x* x* x - 2* x* x* y* y - y* y* y* y))
        	    /(L1*L1 + 2*L1*x - L2*L2 + x*x + y*y));

    ang1 = 2*atan((2*L2*y +  														// Find Ang1
       	sqrt((- L1*L1 + 2*L1*L2 - L2*L2 + x*x + y*y)
           	*(  L1*L1 + 2*L1*L2 + L2*L2 - x*x - y*y)))     
           	/(- L1*L1 + 2*L2*x  + L2*L2 + x*x + y*y));
 
    n1x = L1*cos(ang0); 	n2x = n1x + L2*cos(ang1); 								// Set Nodes
    n1y = L1*sin(ang0); 	n2y = n1y + L2*sin(ang1);}

// ----------------------------- Target Shape Generator ---------------------
void genTarget(int shape, double radius, double numPts, double cx, double cy) {

	for (int i = 0; i < numPts; i++) {	 										
		if (shape == 0) {target[0][i] = cx + radius*cos(double(i)*6.28/numPts), 	// Circle
			             target[1][i] = cy + radius*sin(double(i)*6.28/numPts);}

		if (shape == 1) {target[0][i] = cx + radius*cos(double(i)*6.28/numPts),  	// Flower
			             target[1][i] = cy + radius*sin(double(i)*6.28/numPts);}}}

// ----------------------------- Draw Arm/Drawing ---------------------------------------
void drawArm() {    	   	 														// Draw Arm
    glBegin(GL_LINE_STRIP); glVertex2d(n0x, n0y);
    						glVertex2d(n1x, n1y);
    						glVertex2d(n2x, n2y);    		glEnd();}
void drawDrawing() { 																// Draw Drawing
   	glBegin(GL_POINTS);
    	for (int i = 0; i < ptNum; i++) {
    		glVertex2d(drawing[0][i], drawing[1][i]);}; 	glEnd();}

// ---------------------- Draw The Shapes Function ------------------
void drawLoop() {

	genTarget(0, .3, 40, -.5, -.5);	

	for (int i = 1; i < 40; i++) {
		angNodeSolve(target[0][i],target[1][i]);
	}

	drawShape(0, .3, 40,  .5,  .5);}

//  --------------------------- init/main -----------------------------
int main(int argc, char** argv) {  

	// Init
	glutInit(&argc, argv);                                         
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutCreateWindow("crowTRobot");

 	// Functions
    glutDisplayFunc(drawLoop);
    glutMainLoop();}