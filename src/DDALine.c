#include<stdio.h>
#include<GL/glut.h>

void DDALine(int xa, int ya, int xb, int yb){
    int dx = xb - xa;
    int dy = yb - ya;
    int steps;
    if(dx > dy){
        steps = dx;
    }else{
        steps = dy;
    }

    float xinc = (float)(dx) / steps;
    float yinc = (float)(dy) / steps;

    glBegin(GL_POINTS);
        glVertex2d(xa,ya);
        for(int i=0; i<steps; i++){
            xa+=xinc;
            ya+=yinc;
            glVertex2d(xa,ya);
        }
        
}

void draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
DDAline(100,100,400,200);
glColor3f(0,1,0);
DDALine(100,100,200,400); // half-drawn
glColor3f(0,0,1);
Bline(100,100,400,50);
glColor3f(0,1,1);
Bline(100,100,50,400);
    glEnd();
    glFlush();

}
void main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("DDA_Line");

    glClearColor(0,0,0,0);
    glColor3f(0,1,0);

    gluOrtho2D(0,640,0,480);

    glutDisplayFunc(draw);

    glutMainLoop();


}