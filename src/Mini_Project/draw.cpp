#include<GL/glut.h>
#include<iostream>
using namespace std;
int xc,yc;
int isdrag = 0;

void draw(){
    // glClear(GL_COLOR_BUFFER_BIT);
    // glPointSize(3);
    // glBegin(GL_POINTS);
    // glVertex2d(xc,yc);
    // glEnd();
     //glFlush();

}
void mouse(int button, int state, int x, int y){
    if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        isdrag = 1;
        // xc = x;
        // yc = 480-y;
    }
    else{
        isdrag = 0;
    }
}
void motion(int x, int y){
    if(isdrag){
        xc = x;
        yc = 480 - y;
        
    }
}
void update(){
    if(isdrag){
        //glPointSize(3);
        glBegin(GL_POINTS);
        glVertex2d(xc,yc);
        glEnd();
        glFlush();
        glutPostRedisplay();
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Title");

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glColor3f(0,1,0);

    gluOrtho2D(0,640,0,480);

    glutDisplayFunc(draw);
    glutIdleFunc(update);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}