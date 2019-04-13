// Teapot Test 2 {Silas Henderson 2019}
// -- press  s,    d,    e,     f keys to move
// -- press up, down, left, right keys to turn

#include <GL/freeglut.h>
#include <math.h>

int   programOn =  1;
int   leftKey   =  0, rightKey =   0, upKey =   0, downKey = 0;
int   sKey      =  0, fKey     =   0, eKey  =   0, dKey    = 0;
float camZ      =  1, camX     =   1, camY  =   0;
float theta     = -2, dPos     = .02, dAng  = .02;

// -------------------------------- Keyboard/Timer -----------------------
void keyboard() {
	if (upKey    == 1) {camY += dPos;}
	if (downKey  == 1) {camY -= dPos;}
	if (leftKey  == 1) {theta = theta - dAng;}
	if (rightKey == 1) {theta = theta + dAng;}

	if (eKey     == 1) {camX += dPos*cos(theta); camZ += dPos*sin(theta);}
	if (dKey     == 1) {camX -= dPos*cos(theta); camZ -= dPos*sin(theta);}
	if (fKey     == 1) {camX -= dPos*sin(theta); camZ += dPos*cos(theta);}
	if (sKey     == 1) {camX += dPos*sin(theta); camZ -= dPos*cos(theta);}}

void keyDown(int key, int x, int y) {
	switch (key) {	case GLUT_KEY_LEFT: 	leftKey  = 1; break;
			case GLUT_KEY_RIGHT: 	rightKey = 1; break;
			case GLUT_KEY_DOWN: 	downKey  = 1; break;
			case GLUT_KEY_UP: 	upKey    = 1; break; }}

void keyUp(  int key, int x, int y) {
	switch (key) {	case GLUT_KEY_LEFT: 	leftKey  = 0; break; 
		  	case GLUT_KEY_RIGHT: 	rightKey = 0; break; 
			case GLUT_KEY_DOWN: 	downKey  = 0; break; 
			case GLUT_KEY_UP: 	upKey    = 0; break; }}

void cKeyDown( unsigned char key, int x, int y) {
	if (key == 'd') {dKey = 1;};	if (key == 'e') {eKey = 1;}
	if (key == 's') {sKey = 1;};	if (key == 'f') {fKey = 1;}}

void cKeyUp(   unsigned char key, int x, int y) {
	if (key == 'd') {dKey = 0;};	if (key == 'e') {eKey = 0;}
	if (key == 's') {sKey = 0;};	if (key == 'f') {fKey = 0;}}

// -------------------------- Update Function -----------------------
void update() {

	keyboard();

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 			
	glLoadIdentity();
	gluPerspective(70, 1, .1, 100);

	gluLookAt(camX,               camY, camZ, 
	   	  camX + cos(theta),  camY, camZ + sin(theta), 0, 1, 0);
	
	glutSolidTeapot(.3);
	glutSwapBuffers();}
			 
// ------------------------ Timer/Setup/Main -----------------------
void timer(int dummy) {update(); glutTimerFunc(10, timer, 0);}

int main(int argc, char** argv) {

	// Window
 	glutInit(&argc, argv);
 	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
 	glutCreateWindow("3d");

 	glEnable(GL_DEPTH_TEST);
 	glDepthFunc(GL_LESS);

 	// Material
 	glEnable(GL_COLOR_MATERIAL);
	float matSpec[] = {1, 1, 1, 1};  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    	float matAmbi[] = {0, 1, 0, 1};  glMaterialfv(GL_FRONT, GL_AMBIENT,  matAmbi);
    	float matDiff[] = {0, 0, 1, 1};  glMaterialfv(GL_FRONT, GL_DIFFUSE,  matDiff);

 	// Lighting
   	glEnable(GL_LIGHTING); 							
   	glEnable(GL_LIGHT0);
    	float lightPos[]  = {1, 1, 1, 0};  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    	float lightAmbi[] = {0, 0, 0, 1};  glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbi);
    	float lightSpec[] = {1, 1, 1, 1};  glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
    	float lightDiff[] = {1, 1, 1, 1};  glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiff);

    	// Functions
 	glutDisplayFunc(update);
 	glutSpecialFunc(keyDown);
 	glutSpecialUpFunc(keyUp);
 	glutKeyboardFunc(cKeyDown);
 	glutKeyboardUpFunc(cKeyUp);
 	glutTimerFunc(10, timer, 0);
 	glutMainLoop();}
