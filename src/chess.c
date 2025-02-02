#include<stdio.h>
#include<GL/glut.h>
// #include <windows.h>

int xa=100,ya=100,xb=420,yb=420,n=8;

void DDALine(int xa, int ya, int xb, int yb){
    
    glVertex2d(xa,ya);
    glVertex2d(xb,yb);

    
}

void Draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    int d = (yb-ya)/n;
    
    int yt = ya;
    for(int i=0; i<n+1; i++){
        DDALine(xa,yt,xb,yt);
        yt = yt + d;
        Sleep(5);
    }

    int xt = xa;
    for(int i=0; i<n+1; i++){
        DDALine(xt,ya,xt,yb);
        xt = xt + d;
    }

    glEnd();
    glFlush();

}


void main(int argc, char** argv){
    // printf("Enter Co-ordinates of Bottom-Left Vertex ->\n");
    // printf(" X1 :");
    // scanf("%d",&xa);
    // printf(" Y1 :");
    // scanf("%d",&ya);

    // printf("Enter Co-ordinates of Top-Right Vertex ->\n");
    // printf(" X2 :");
    // scanf("%d",&xb);
    // printf(" Y2 :");
    // scanf("%d",&yb);

    // prin tf("Enter no of Rows/Colums :");
    // scanf("%d",&n);

    glutInit (&argc , argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("Chess");

    glClearColor(0.0, 0.0, 0.0, 0);
    glColor3f(0.0,1.0,0.0);

    gluOrtho2D(0,640,0,480);

    glutDisplayFunc(Draw);
    glutMainLoop();

    return;
}