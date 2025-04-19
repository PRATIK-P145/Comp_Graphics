#include<iostream>
#include<GL/glut.h>
#include<math.h>
using namespace std;

int isDragging = 0;
int xc,yc,xb,yb;
int r;
// Function to plot symmetric points for the circle
void plotCirclePoints(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
    glEnd();
}

// Bresenham's Circle Drawing Algorithm
void BresCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r; // Decision parameter

    while (x <= y) {
        plotCirclePoints(xc, yc, x, y);
        glFlush(); // Update display after plotting points

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 15;
            y--;
        }
        x++;
        //Sleep(50); // Delay of 50 milliseconds
    }
}

void MouseClick(int button, int state, int x, int y){
    int normX = x;
    int normY = 480-y;
     if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ){
        xc = normX;
        yc = normY;
        isDragging = 1;
     }else{
        isDragging = 0;
     }
}
void Motiondetect(int x, int y){
     if(isDragging == 1){
        xb = x;
        yb = 480-y;
        
        r = sqrt(((xb-xc)*(xb-xc))+((yb-yc)*(yb-yc)));
     }
}

void draw(){
    //glClear(GL_COLOR_BUFFER_BIT);
    if(isDragging == 1){
    glBegin(GL_LINES);
        cout<<xc<<","<<yc<<" & "<<xb<<","<<yb<<endl;
        glVertex2d(xc,yc);
        glVertex2d(xb,yb);
         BresCircle(xc,yc,r);
    glEnd();
    glFlush();
    }
    glFlush();
}

void update(){
    glutPostRedisplay();
}

int main(int argc,char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("Window");

    glClearColor(0,0,0,0);
    glColor3f(0,1,0);

    gluOrtho2D(0,640,0,480);

    glutDisplayFunc(draw);
    glutIdleFunc(update);
    glutMouseFunc(MouseClick);
    glutMotionFunc(Motiondetect);
    glutMainLoop();

    return 0;
}