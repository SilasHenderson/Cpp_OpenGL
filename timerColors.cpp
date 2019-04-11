// color-changing-screen {Silas Henderson 2019}

#include <GL/glut.h>
#include <math.h>

float colorAng = 0;

void draw() {
    colorAng = colorAng + .02;
    glClearColor(cos(colorAng), cos(1.5*colorAng), cos(2*colorAng), 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glRectf(0, 0, .5, .5);
    glutSwapBuffers();}

void timer(int value) {
    draw();
    glutTimerFunc(10, timer, 0);
    glutPostRedisplay();}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutCreateWindow("crowTRobot");
    glutDisplayFunc(draw);
    glutTimerFunc(50, timer, 0);
    glutMainLoop(); }