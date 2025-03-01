#include <GL/glut.h>
// #include <vector>
// using namespace std;

int x2=0,  y2=0;
int xi=0, yi=0;
int x1=0, y_1=0;
int count =0;
int start =1;
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
        start =0;
        count++;
        glPointSize(3.0);
        glBegin(GL_POINTS);
        glVertex2f(x,480-y);
        glEnd();
        glFlush();
        if(count == 1){
            xi = x;
            yi = y;
            x1=xi;  // x-previous
            y_1=yi;  // y-previous
            
        }else {
            x2 = x;
            y2 = y;
           Draw(x2,(480-y2),x1,(480-y_1));

           if(x2==x1 && y2 == y_1){
             //glClear(GL_COLOR_BUFFER_BIT);
             Draw(x2,(480-y2),xi,(480-yi));
             count = 0;
           } 
           x1 = x2;
           y_1 = y2;
        }       
    }
}

void Display(){
    if(start==1){
        glClear(GL_COLOR_BUFFER_BIT);
         glFlush();
     }
  // glClear(GL_COLOR_BUFFER_BIT);
    // glPointSize(3.0);
    // glBegin(GL_POINTS);
    //  if(count == 1){
    //     glVertex2f(x,480-ya);   
    //  }else{
    //     glVertex2f(xb,480-yb);
    //     Draw(xa,(480-ya),xb,(480-yb));
    //  }
    //  glEnd();
    // glFlush();
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