
// drawing robot-2d opengl {Silas Henderson}

// -------------------------- Setup  -----------------------
#include <iostream>
#include <chrono>
#include <GL/glut.h>
#include <math.h>
													
double L1 = .8;		double n0x = 0;		double ang0 = 0, ang1 = 0;	
double L2 = .8;		double n0y = 0;		double n1x, n1y, n2x, n2y;  			

double path[2][100];		int pathPtCount    = 100;									
double target[2][100]; 		int targetPtCount  = 100; 						
double drawing[2][2000];	int drawingPtCount = 0; 	      

// ------------------------ Pause Function -----------------------------
void pause(double DT) {      						
	glutSwapBuffers();								// -- swap buffers
	auto t0 = std::chrono::system_clock::now(); 	// -- timer
	while (1) {	
		auto t1 = std::chrono::system_clock::now(); 
		std::chrono::duration<double> dt = t1 - t0; 
		if (dt.count() > DT) {break;}}              

	glClear(GL_COLOR_BUFFER_BIT);}                  // -- glClear

// -------------------------- Angle/Node Solver ---------------------------
void angNodeSolve(double x, double y) { 			

    ang0 = 2*atan((2*L1*y - 			 												
    	sqrt( 	-   L1*L1*L1*L1 + 2*L1*L1*L2*L2 -   L2*L2*L2*L2 
          	+ 2*L1*L1* x* x + 2*L1*L1* y* y + 2*L2*L2* x* x 
           	+ 2*L2*L2* y* y -    x* x* x* x - 2* x* x* y* y - y* y* y* y))
        	  /(L1*L1 + 2*L1*x - L2*L2 + x*x + y*y));

    ang1 = 2*atan((2*L2*y +  																	
       	sqrt(( - L1*L1 + 2*L1*L2 - L2*L2 + x*x + y*y)
             *(  L1*L1 + 2*L1*L2 + L2*L2 - x*x - y*y)))     
             /(- L1*L1 + 2*L2*x  + L2*L2 + x*x + y*y));
 
    n1x = L1*cos(ang0); 	n2x = n1x + L2*cos(ang1); 								
    n1y = L1*sin(ang0); 	n2y = n1y + L2*sin(ang1);}

// ----------------------------- Target Points Generator ---------------------
void targetGen(int shape, double radius, double numPts, double cx, double cy) {      

	for (int i = 0; i < numPts; i++) {		

		double di = 6.28*double(i)/numPts;

		if (shape == 0) {	target[0][i] = cx + radius*cos(di);
			             	target[1][i] = cy + radius*sin(di);}

		if (shape == 1) {	target[0][i] = cx + radius*cos(2*di)*cos(di); 
			             	target[1][i] = cy + radius*cos(2*di)*sin(di);}
		
		if (shape == 2) {	target[0][i] =  cx + (di/6.28)*radius*cos(3*di);
					target[1][i] =  cy + (di/6.28)*radius*sin(3*di);}}}

// ----------------------------- Short Functions -----------------------
void pathGen() { 										
	for (int i = 0; i < pathPtCount; i++) {
		path[0][i] = (target[0][i] - n2x)*double(i)/pathPtCount + n2x;
		path[1][i] = (target[1][i] - n2y)*double(i)/pathPtCount + n2y;}}

void drawArm() { glBegin(GL_LINE_STRIP); 	glVertex2d(n0x, n0y);
    				  	 	glVertex2d(n1x, n1y);
    						glVertex2d(n2x, n2y);   glEnd();}
void drawDrawing() { 																
	glBegin(GL_POINTS);
   	for (int i = 0; i < drawingPtCount; i++) {
    		glVertex2d(drawing[0][i], drawing[1][i]);}; glEnd();}

void addPt() {	drawing[0][drawingPtCount] = n2x;  		
		drawing[1][drawingPtCount] = n2y;	
		drawingPtCount++;}   

void drawTarget() {		
	for (int i = 0; i < targetPtCount; i++) {  					
		angNodeSolve(target[0][i],target[1][i]);	    
		addPt();		drawArm();	
		drawDrawing();		pause(.01);}}      

void moveArm() {
	for (int i = 0; i < pathPtCount; i++){
		angNodeSolve(path[0][i], path[1][i]);
		drawArm(); drawDrawing(); pause(.01);}}

// ---------------------- Draw The Shapes Function ------------------
void loop() {
	angNodeSolve(.1, .1);
	
	targetGen(0, .3, 100, -.5, -.5); pathGen();	moveArm(); drawTarget();
	targetGen(1, .3, 100,  .5, -.5); pathGen();	moveArm(); drawTarget();
	targetGen(2, .3, 100,  .5,  .5); pathGen();	moveArm(); drawTarget();
	targetGen(0, .3, 100, -.5,  .5); pathGen();	moveArm(); drawTarget();}

//  --------------------------- init/main -----------------------------
int main(int argc, char** argv) {  

	glutInit(&argc, argv);                                         
    	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    	glutCreateWindow("crowTRobot");

    	glutDisplayFunc(loop);
    	glutMainLoop();}
