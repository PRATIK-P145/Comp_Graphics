#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define PI 3.14159265358979323846

int ROUND(float a){
    return (int)(a+0.5);
}

void DDALine(int xa, int ya, int xb, int yb){
    int dx = xb - xa;
    int dy = yb - ya;
    int steps;
    if(abs(dx) > abs(dy)){
        steps = abs(dx);
    }else{
        steps = abs(dy);
    }

    float x, y;
    x = xa;
    y = ya;

    float xinc = (float)(dx) / steps;
    float yinc = (float)(dy) / steps;

    glBegin(GL_POINTS);
    glVertex2d(xa,ya);
    for(int i=0; i<steps; i++){
        x+=xinc;
        y+=yinc;
        glVertex2d(ROUND(x),ROUND(y));
    }  
    glEnd();      
}

void ddaLine(int xa, int ya, int xb, int yb){
    glBegin(GL_LINES);
    glVertex2d(xa,ya);
    glVertex2d(xb,yb);
    glEnd();
}

int count = 3;

void Koch(int xa, int ya, int xb, int yb, int count){
    float x1, y1, x2, y2, rdx, rdy;

    x1 = xa + (xb-xa)/3;
    y1 = ya + (yb-ya)/3;

    x2 = xa + 2*(xb-xa)/3;
    y2 = ya + 2*(yb-ya)/3;


    float dx = x2-x1;
    float dy = y2-y1;

    float angle = -PI/3;
    rdx = dx*cos(angle) - dy*sin(angle);
    rdy = dx*sin(angle) + dy*cos(angle);

    float x3 = x1 + rdx;
    float y3 = y1 + rdy;


    if (count == 0) {
        DDALine(xa,ya,xb,yb);
        return;
    }
        Koch(xa,ya, x1, y1,count-1);
        Koch(x1,y1,x3,y3,count-1);
        Koch(x3,y3,x2,y2,count-1);
        Koch(x2,y2,xb,yb,count-1);


}

void draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    Koch(100,200,600,200,count);
    Koch(600,200,350,400,count);
    Koch(350,400,100,200,count);
    glFlush();

}

void main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("Koch curve.......");

    glClearColor(0,0,0,0);
    

    gluOrtho2D(0,640,0,480);

    glutDisplayFunc(draw);

    glutMainLoop();


}
