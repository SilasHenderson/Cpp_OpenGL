// Robot Arm 2d (opengl version) {Silas Henderson}

#include <math.h>
#include <GL/freeglut.h>

int   ptNum = 0; 			float ang[2] = { 0,  0};  	
float pts[3][2000];			float node[3][3];

float shapePts[3][200];
int   shapePtNum = 0;

int upKey = 0, downKey = 0, leftKey = 0, rightKey = 0; 
int dKey  = 0, fKey    = 0;

int program = 0;

float x = .2, y = .2, radius = .3;
// ------------------------ Options -------------------
float L[2]   = {.5, .5};

float dAng   = .05;
float ptSize =   2;

// ------------------ Get-Angle Functions ---------------- //

float pos2Ang(float x, float y, float L1, float L2) {

    ang[0] = 2*atan((2*L1*y - 
       	sqrt( -   L1*L1*L1*L1 + 2*L1*L1*L2*L2 -   L2*L2*L2*L2 
              + 2*L1*L1* x* x + 2*L1*L1* y* y + 2*L2*L2* x* x 
              + 2*L2*L2* y* y -    x* x* x* x - 2* x* x* y* y - y* y* y* y))
        /(L1*L1 + 2*L1*x - L2*L2 + x*x + y*y));

    ang[1] = 2*atan((2*L2*y + 
        sqrt((- L1*L1 + 2*L1*L2 - L2*L2 + x*x + y*y)
            *(  L1*L1 + 2*L1*L2 + L2*L2 - x*x - y*y)))     
            /(- L1*L1 + 2*L2*x  + L2*L2 + x*x + y*y));}

// ------------------ Define Shape Points Functions ----------------------- //
void ang2Node() {

	node[0][1] = L[0]*cos(ang[0]);  
	node[1][1] = L[0]*sin(ang[0]); 
	node[2][1] = 0;			   	    
	
	node[0][2] = L[0]*cos(ang[0]) + L[1]*cos(ang[1]);
 	node[1][2] = L[0]*sin(ang[0]) + L[1]*sin(ang[1]);
 	node[2][2] = 0;}

void addPt(){ pts[0][ptNum] = node[0][2];
	          pts[1][ptNum] = node[1][2];
	          pts[2][ptNum] = node[2][2]; 	ptNum = ptNum + 1;}

void drawArm() {
	glBegin(GL_LINE_STRIP);
		glVertex3f(node[0][0], node[1][0], node[2][0]);
		glVertex3f(node[0][1], node[1][1], node[2][1]);
		glVertex3f(node[0][2], node[1][2], node[2][2]);
	glEnd();}

void drawPts() {
	glBegin(GL_POINTS);
	for (int i = 0; i < ptNum; i++) {
		glVertex3f(pts[0][i], pts[1][i], pts[2][i]);}; glEnd();}

// ------------------------------ Animation ------------------
void circlePts() {

	for (int i = 0; i < shapePtNum; i = i + 1) {  
 		float angle = float(i)*6.28/float(shapePtNum);

 		shapePts[0][i] = x + radius*cos(angle);       
		shapePts[1][i] = y + radius*sin(angle);}}

// --------------------------- Keyboard/Mouse -----------------
void arrowDown(int key, int x, int y) { 
	switch (key) {
		case GLUT_KEY_UP:   	upKey    = 1; 	break;
		case GLUT_KEY_DOWN:		downKey  = 1;	break; 
		case GLUT_KEY_LEFT: 	leftKey  = 1; 	break;
		case GLUT_KEY_RIGHT: 	rightKey = 1;	break;}}

void arrowUp(  int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:   	upKey    = 0; 	break;
		case GLUT_KEY_DOWN:		downKey  = 0; 	break;
		case GLUT_KEY_LEFT: 	leftKey  = 0; 	break;
		case GLUT_KEY_RIGHT: 	rightKey = 0; 	break;}}

void keyDown( unsigned char key, int x, int y) {
	if (key == 'd') {dKey = 1;}		if (key == 'f') {fKey = 1;}}

void keyUp( unsigned char key, int x, int y) {
	if (key == 'd') {dKey = 0;}  	if (key == 'f') {fKey = 0;}}

// -------------------------- Loop ----------------------------------
void loop() {

	if (fKey == 1) {glClearColor(.1, .4, .2, 1);}
	if (fKey == 0) {glClearColor(.1, .1, .1, 1);}

	glClear(GL_COLOR_BUFFER_BIT);
	if (program == 0) {
		
		if (leftKey  == 1) {ang[0] = ang[0] - dAng; } 		
		if (rightKey == 1) {ang[0] = ang[0] + dAng; }
		if (upKey    == 1) {ang[1] = ang[1] + dAng; }
		if (downKey  == 1) {ang[1] = ang[1] - dAng; }
		
		if (dKey == 1) {addPt();}} 							

	if (program == 1) {}

	ang2Node();
	drawArm(); 												
	drawPts();
	glutSwapBuffers();}

// ---------------------------- Timer/Main ------------------
void timer(int value) {loop(); glutTimerFunc(10, timer, 0);} 

int main(int argc, char** argv) {  

	// Init
	glutInit(&argc, argv);                                                
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutCreateWindow("crowTRobot");

 	// Extra
 	node[0][0] = 0; 	node[1][0] = 0; 	node[2][0] = 0;
 	glClearColor(.1, .1, .1, 1);
 	glPointSize(ptSize);

 	// Functions
    glutDisplayFunc(loop);
    glutTimerFunc(40, timer, 0);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutSpecialFunc(arrowDown);
    glutSpecialUpFunc(arrowUp);
    glutMainLoop();}