#include <GL/freeglut.h>
#include <vector>
#include <cmath>
#include<iostream>
using namespace std;

int x, y;
int i=0;
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glVertex2d(x,y);
    glEnd();
    glFlush();

}

void mouse(int button, int state, int xi, int yi) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
         x = xi;
         y = 480-yi;
    }
}

bool isPixelEmpty(int x, int y) {
    float pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixel);

    return (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0);
}

void update(){
    //i++;
    if(isPixelEmpty(x,y-1) && y>=1){
        y--;
    }
    //cout<<"i="<<i<<endl;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Sand");

    glClearColor(0,0,0,0);
    glColor3f(1,1,0);

    gluOrtho2D(0,640,0,480);
    
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutIdleFunc(update);

    //glutMotionFunc(motion);
   // glutKeyboardFunc(keyboard);

    glutMainLoop();
    
    return 0;
}