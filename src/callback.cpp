#include<iostream>
#include<GL/glut.h>
using namespace std;

int x1=150, y_1=150;
int xa,ya,xb,yb;
float scale;


void draw(int x, int y){
    // xa = x*sc;
    // ya = y*sc;
    // xb = (x+200)*sc;
    // yb = (y+150)*sc;

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
        glVertex2d(x,y);
        glVertex2d(x+200, y);
        glVertex2d(x+200, y+150);
        glVertex2d(x,y+150);
    glEnd();
    glFlush();
}
// void drag(int x, int y){
//     scale = (x/15)+(x%15);
//     int y2 = y*scale;
//     int x2 = (x+200)*scale;
//     cout<<"Curser at : ("<<x2<<","<<y2<<" )\n Scale:"<<scale<<endl;


//     //glClear(GL_COLOR_BUFFER_BIT);

//     draw(x1,y_1,scale);
// }

void drag(int x, int y){
    x1 = x;
    y_1 = 480-y;

    glClear(GL_COLOR_BUFFER_BIT);

    draw(x1, y_1);

}
void display(){
     glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
        glVertex2d(x1,y_1);
        glVertex2d(x1+200, y_1);
        glVertex2d(x1+200, y_1+150);
        glVertex2d(x1,y_1+150);
    glEnd();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);

    //glutCreateMenu();
    glutCreateWindow("Callback");

    glClearColor(0,0,0,0);
    glColor3f(0.0, 1.0, 0.0);

    gluOrtho2D(0,640,0,480);

    glutDisplayFunc(display);
    glutMotionFunc(drag);
    glutMainLoop();


    return 0;
}