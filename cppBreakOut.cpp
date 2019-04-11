// break-out {Silas Henderson 2019}

#include <GL/freeglut.h>                                                   
#include <math.h>                                                         

int programOn  = 1;     float boxPos   =  0;                                                         
int leftKey    = 0;     float ballPosX =  3;    float ballVelX = .02;                                                           
int rightKey   = 0;     float ballPosY = .8;    float ballVelY = .02;

void update() {                                                             
    glClear(GL_COLOR_BUFFER_BIT);                                         

    if (ballPosX <  -1 || ballPosX > 1) {ballVelX = -ballVelX;}           
    if (ballPosY < -.8 || ballPosY > 1) {ballVelY = -ballVelY;}             

    if (ballPosY < -.8 && abs(ballPosX - boxPos) > .2) {programOn = 0;}       
    
    ballPosX = ballPosX + ballVelX;                                     
    ballPosY = ballPosY + ballVelY;

    if (leftKey  == 1) {boxPos = boxPos - .05;}                      
    if (rightKey == 1) {boxPos = boxPos + .05;}

    glRectf(boxPos - .2, -.9, boxPos + .2, -.8);  
    glBegin(GL_POINTS); 
        glVertex2f(ballPosX, ballPosY); 
    glEnd(); 
    
    glutSwapBuffers();                                             
    if (programOn == 0) { glutDestroyWindow(1);  return;}}    

void keyDown(int key, int x, int y) {                                     
    switch (key) {  case GLUT_KEY_LEFT:    leftKey = 1; break;
                    case GLUT_KEY_RIGHT:  rightKey = 1; break; }}

void keyUp(  int key, int x, int y) {                                   
    switch(key) {   case GLUT_KEY_LEFT:    leftKey = 0; break; 
                    case GLUT_KEY_RIGHT:  rightKey = 0; break; }}

void timer(int value) {update(); glutTimerFunc(10, timer, 0);}            

int main(int argc, char** argv) {                                         
    glutInit(&argc, argv);                                             
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutCreateWindow("crowTRobot");
    
    glClearColor(.1, .1, .1, 1);                                
    glPointSize(10);                               

    glutDisplayFunc(update);                                      
    glutSpecialFunc(keyDown);
    glutSpecialUpFunc(keyUp);
    glutTimerFunc(40, timer, 0);
    glutMainLoop();}
