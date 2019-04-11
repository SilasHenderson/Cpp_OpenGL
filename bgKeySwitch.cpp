// cppGL color switch {Silas Henderson 2019} 
// -- up/down key change window color

#include <GL/glut.h> 										
float red = .1; 		

void keyboard(int key, int x, int y) {   					        
	switch (key) {
		case GLUT_KEY_UP:    red = .5; glutPostRedisplay(); break;
		case GLUT_KEY_DOWN:  red = .1; glutPostRedisplay(); break;}}

void display() { 											
	glClearColor(red, .1, .1, 1);						
	glClear(GL_COLOR_BUFFER_BIT);  						
	glutSwapBuffers();} 								

int main(int argc, char **argv) { 							
	glutInit(&argc, argv); 								
	glutInitDisplayMode(GLUT_RGB| GLUT_DOUBLE); 			
	glutCreateWindow("bananas");                        	

	glutDisplayFunc(display); 								
	glutSpecialFunc(keyboard);                      		
	glutMainLoop();}                   						
