#include<GL\freeglut.h>
#include<iostream>
using namespace std;
int col[3]={0,0,1};

void line(int x1, int y1, int x2, int y2){
    glVertex2d(x1,y1);
    glVertex2d(x2,y2);
}

void draw(){
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(3.0);
    glBegin(GL_LINES);
        // line(319,239,371,239);
        // line(371,239,371,291);
        // line(371,291,319,291);
        // line(319,291,319,239);
        glColor3f(0,1,0);
        glVertex2d(320,240);
        glVertex2d(370,240);
        glVertex2d(370,240);
        glVertex2d(370,290);

        glColor3f(1,0,1);
        glVertex2d(370,290);
        glVertex2d(320,290);
        glVertex2d(320,290);
        glVertex2d(320,240);
    glEnd();

    glFlush();

    glColor3f(col[0],col[1],col[2]);

    glBegin(GL_POLYGON);
    glVertex2d(320,240);
    glVertex2d(370,240);
    glVertex2d(370,290);
    glVertex2d(320,290);
    glEnd();

    glFlush();

}
void mouse(int button, int state, int x, int y){
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        cout<<x<<" , "<<y<<endl;
        int normY = 480-y;
        if(x<370 && x>320 && normY<290 && normY>240){
            cout<<"Button is pressed"<<endl;
            col[0]=0;col[1]=1;col[2]=1;
        }else{
            col[0]=0;col[1]=0;col[2]=1;
        }
        
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("Title");

    glClearColor(0,0,0,0);
    glColor3f(0,1,0);

    gluOrtho2D(0,640,0,480);

    glutDisplayFunc(draw);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}