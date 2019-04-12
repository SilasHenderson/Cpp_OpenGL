// Teapot Test {Silas Henderson 2019}
// -- press up, down, left, right arrows to move

#include <GL/freeglut.h>
#include <math.h>

int programOn = 1;

int leftKey = 0, rightKey = 0, upKey = 0, downKey = 0;
float camZ  = 1, camX     = 1, theta = -2.5;

// -------------------------------- Keyboard/Timer -----------------------
void keyboard() {
	if (leftKey  == 1) {theta = theta - .02;}
	if (rightKey == 1) {theta = theta + .02;}
	if (upKey    == 1) {camX += cos(theta)/40; camZ += sin(theta)/40;}
	if (downKey  == 1) {camX -= cos(theta)/40; camZ -= sin(theta)/40;}}

void keyDown(int key, int x, int y) {
	switch (key) {case GLUT_KEY_LEFT: 		leftKey  = 1; break;
				  case GLUT_KEY_RIGHT: 		rightKey = 1; break;
				  case GLUT_KEY_DOWN: 		downKey  = 1; break;
				  case GLUT_KEY_UP: 		upKey    = 1; break; }}

void keyUp(  int key, int x, int y) {
	switch (key) {case GLUT_KEY_LEFT: 		leftKey  = 0; break; 
				  case GLUT_KEY_RIGHT: 		rightKey = 0; break; 
				  case GLUT_KEY_DOWN: 		downKey  = 0; break; 
				  case GLUT_KEY_UP: 		upKey    = 0; break; }}

// -------------------------- Update Function -----------------------
void update() {
	keyboard();
	glClear(GL_COLOR_BUFFER_BIT); 			

	glLoadIdentity();
	gluPerspective(70, 1, .1, 100);
	gluLookAt(camX,               0, camZ, 
	   		  camX + cos(theta),  0, camZ + sin(theta), 0, 1, 0);
	
	glutSolidTeapot(.3);
	// glutSolidSphere(1, 20, 20);					
	glutSwapBuffers();}
			 
// ------------------------ Timer/Setup/Main -----------------------
void timer(int dummy) {update(); glutTimerFunc(10, timer, 0);}

int main(int argc, char** argv) {

	// Window
 	glutInit(&argc, argv);
 	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
 	glutCreateWindow("3d");

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
 	glutTimerFunc(10, timer, 0);
 	glutMainLoop();}