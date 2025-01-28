#include <GL/glut.h>
// #include <vector>
// using namespace std;

int xa=0, ya=0,  xb=0,  yb=0;
int count =0;
//int arr[] = {1,2,3,4}; 

void Draw(float xa, float ya,float xb, float yb){
    glBegin(GL_LINES);
        glVertex2f(xa,ya);
        glVertex2f(xb,yb);
    glEnd();
    glFlush();
}

void MouseClick(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        count++;
        if(count == 1){
            xa = x;
            ya = y;
        }else if(count == 2){
            xb = x;
            yb = y;
            count = 0;
           // Draw(xa,(480-ya),xb,(480-yb));
        }
            
    }



}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
     if(count == 1){
        glPointSize(3.0);
        glBegin(GL_POINTS);
        glVertex2f(xa,480-ya);
        glEnd();
        glFlush();
     }else{
        Draw(xa,(480-ya),xb,(480-yb));
     }
    glFlush();
}

void main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutCreateWindow("MOuse Line");

    glClearColor(0,0,0,0);
    glColor3f(0,1,0);
    gluOrtho2D(0,640,0,480);

    glutDisplayFunc(Display);
    glutMouseFunc(MouseClick);

    glutMainLoop();


  return;
}