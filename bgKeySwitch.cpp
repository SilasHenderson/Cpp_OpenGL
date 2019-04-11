// cppGL color switch {Silas Henderson 2019}
// -- press up and down key to change window color
#include <GL/glut.h> 										// gl Utility toolbox

float red = .1; 		

void keyboard(int key, int x, int y) {   					// Keyboard        
	switch (key) {
		case GLUT_KEY_UP:    								// -- up arrow
			red = .5; glutPostRedisplay(); break;
		case GLUT_KEY_DOWN:                             	// -- down arrow
			red = .1; glutPostRedisplay(); break;}}

void display() { 											// Display
	glClearColor(red, .1, .1, 1);							// -- color
	glClear(GL_COLOR_BUFFER_BIT);  							// -- clear
	glutSwapBuffers();} 									// -- update

int main(int argc, char **argv) { 							// Main
	glutInit(&argc, argv); 									// -- initialize ut
	glutInitDisplayMode(GLUT_RGB| GLUT_DOUBLE); 			// -- display props
	glutCreateWindow("bananas");                        	// -- open window

	glutDisplayFunc(display); 								// -- display Fcn
	glutSpecialFunc(keyboard);                      		// -- keyboard Fcn
	glutMainLoop();}                   						// -- main Fcn
