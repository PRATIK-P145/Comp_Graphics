#include <stdio.h>
#include<GL/glut.h>

void Rectangle(int xa, int ya, int xb, int yb){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    glVertex2d(xa,ya);  glVertx2d(xb,ya);
    glVertex2d(xa,yb);  glVertx2d(xb,yb);
    glVertex2d(xa,ya);  glVertx2d(xa,yb);
    glVertex2d(xb,ya);  glVertx2d(xb,yb);

    glEnd();
    glFlush();
}
void Draw(){
    Rectangle(100,100,500,300);
}

int main(int argc,char** argv){

    glutInit(&argc , argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowPosition(0,0);
    // these lines are used to place window at the top of the the screen
    glutInitWindowSize(640,480);
    glutCreateWindow(" Draw ");

    glClearColor(0.0,0.0,0.0,0);
    glColor3f(0.0,1.0,0.0);

    gluOrtho2D(0,640,0,480);

    glutDisplayFunc(Draw);
    glutMainLoop();


return 0;
}