// break-out {Silas Henderson 2019}

#include <GL/freeglut.h>                                                    // libraries
#include <math.h>                                                         

int programOn = 1;                                                          // program switch

int leftKey  = 0;                                                           // key flags
int rightKey = 0;

float boxPos   =   0;                                                       // box pos
float ballPosX =  .3;    float ballVelX = .02;
float ballPosY =  .8;    float ballVelY = .02;

void update() {                                                             // Update Function
    glClear(GL_COLOR_BUFFER_BIT);                                           // -- clear

    if (ballPosX <  -1 || ballPosX > 1) {ballVelX = -ballVelX;}             // -- bounce
    if (ballPosY < -.8 || ballPosY > 1) {ballVelY = -ballVelY;}             

    if (ballPosY < -.8 && abs(ballPosX - boxPos) > .2) {programOn = 0;}     // -- close if miss         
    
    ballPosX = ballPosX + ballVelX;                                         // -- update pos
    ballPosY = ballPosY + ballVelY;

    if (leftKey  == 1) {boxPos = boxPos - .05;}                             // -- move box
    if (rightKey == 1) {boxPos = boxPos + .05;}

    glRectf(boxPos - .2, -.9, boxPos + .2, -.8);                            // -- draw box
    glBegin(GL_POINTS); glVertex2f(ballPosX, ballPosY); glEnd();            // -- draw ball
    
    glutSwapBuffers();                                                      // -- refresh

    if (programOn == 0) { glutDestroyWindow(1);  return;}}                  // -- if(close)

// ------------------------------ Keyboard ----------------------------
void keyDown(int key, int x, int y) {                                       // Key Down
    switch (key) {  case GLUT_KEY_LEFT:    leftKey = 1; break;
                    case GLUT_KEY_RIGHT:  rightKey = 1; break; }}

void keyUp(  int key, int x, int y) {                                       // Key Up
    switch(key) {   case GLUT_KEY_LEFT:    leftKey = 0; break; 
                    case GLUT_KEY_RIGHT:  rightKey = 0; break; }}

// --------------------------- Timer, Main ----------------------------
void timer(int value) {update(); glutTimerFunc(10, timer, 0);}              // Timer

int main(int argc, char** argv) {                                           // Main
    glutInit(&argc, argv);                                                  // -- init/window
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutCreateWindow("crowTRobot");
    
    glClearColor(.1, .1, .1, 1);                                            // -- graphics
    glPointSize(10);                               

    glutDisplayFunc(update);                                                // -- functions
    glutSpecialFunc(keyDown);
    glutSpecialUpFunc(keyUp);
    glutTimerFunc(40, timer, 0);
    glutMainLoop();}