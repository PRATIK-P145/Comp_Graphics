#include <stdio.h>
#include<math.h>
#include<GL/glut.h>

int xa,ya,xb,yb;

void Draw(){
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0.0f, 1.0f, 1.0f); // Set polygon color (dark)
    
    glBegin(GL_POLYGON); // Start polygon
        // glVertex2d(-100,-100);
        // glVertex2d(-100, 100);
        // glVertex2d(100, 100);
        // glVertex2d(100, -100);

         glVertex2d(-40, -60);
        glVertex2d(40, -60);
        glVertex2d(80, 0);
        glVertex2d(40, 60);
        glVertex2d(-40, 60);
        glVertex2d(-80, 0);
    glEnd(); // End polygon
    glFlush();

    glLineWidth(3.0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2d(0,-230);
        glVertex2d(0,230);

        glVertex2d(-310,0);
        glVertex2d(310,0);

    glEnd();
    glFlush();
   
}



int main(int argc,char** argv){

    glutInit(&argc , argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow(" Draw ");

    glClearColor(0.0,0.0,0.0,0);
    glColor3f(0.0,1.0,0.0);

    gluOrtho2D(-320,320,-240,240);

    glutDisplayFunc(Draw);
    glutMainLoop();


  return 0;

}