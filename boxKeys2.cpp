
#include <GL/glut.h>
#include <math.h>

float bx = 0;
float by = 0;

void refresh() {
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(bx - .1, by - .1, bx + .1, by + .1);
	glutSwapBuffers();}

void keyboard(int key, int x, int y) { 
	switch (key) {
		case GLUT_KEY_LEFT:  	bx = bx - .1; 	break;
		case GLUT_KEY_RIGHT: 	bx = bx + .1; 	break;
		case GLUT_KEY_DOWN: 	by = by - .1; 	break;
		case GLUT_KEY_UP:	by = by + .1; 	break;}
	refresh();}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("its_rectangle_time");
	glutDisplayFunc(refresh);
	glutSpecialFunc(keyboard);
	glutMainLoop();}
