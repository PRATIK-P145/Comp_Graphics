#include <stdio.h>
#include<math.h>
#include<GL/glut.h>

int xa,ya,xb,yb;

void plotCirclePoints(int xc, int yc, int x, int y) {

    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
    glEnd();

}

// Bresenham's Circle Drawing Algorithm
void BresCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r; // Decision parameter

    while(x <= y) {
        plotCirclePoints(xc, yc, x, y);
        glFlush(); // Update display after plotting points

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 15;
            y--;
        }
        x++;
       // Sleep(50); // Delay of 50 milliseconds
    }
}

void Rect(int xa, int ya, int xb, int yb){

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    glVertex2d(xa,ya);  glVertex2d(xb,ya);
    sleep(20);
    glVertex2d(xa,yb);  glVertex2d(xb,yb);
    sleep(20);
    glVertex2d(xa,ya);  glVertex2d(xa,yb);
    sleep(20);
    glVertex2d(xb,ya);  glVertex2d(xb,yb);



    int mx1,my_1, mx2,my2, mx3,my3, mx4,my4;

    mx1 = (int)(xa+xb)/2;  my_1 = ya;
    mx2 = xb;              my2 = (int)(ya+yb)/2;
    mx3 = (int)(xa+xb)/2;  my3 = yb;
    mx4 = xa;              my4 = (int)(ya+yb)/2;

    sleep(20);
    
    glVertex2d(mx1,my_1);  glVertex2d(mx2,my2);
    glVertex2d(mx2,my2);  glVertex2d(mx3,my3);
    glVertex2d(mx3,my3);  glVertex2d(mx4,my4);
    glVertex2d(mx4,my4);  glVertex2d(mx1,my_1);


    
    int cx = mx1 , cy = my2;
    int diag1 = sqrt( (mx3-cx)*(mx3-cx) + (my3-cy)*(my3-cy) );
    int diag2 = sqrt( (mx4-cx)*(mx4-cx) + (my4-cy)*(my4-cy) );
    int side  = sqrt( (mx4-mx3)*(mx4-mx3) + (my4-my3)*(my4-my3) );

    int r = (diag1 * diag2)/side;

    BresCircle(mx1,my2,r);

    glEnd();
    glFlush();

}
void Draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    Rect(xa,ya,xb,yb);
    //Rect(150,50,600,350);
}



int main(int argc,char** argv){

    //int xa,ya,xb,yb;
    printf("Enter Co-ordinates of Bottom-Left Vertex ->\n");
    printf(" X1 :");
    scanf("%d",&xa);
    printf(" y_1 :");
    scanf("%d",&ya);

    printf("Enter Co-ordinates of Top-Right Vertex ->\n");
    printf(" X2 :");
    scanf("%d",&xb);
    printf(" Y2 :");
    scanf("%d",&yb);

    glutInit(&argc , argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowPosition(0,0);

    glutInitWindowSize(640,480);
    glutCreateWindow(" Problem 2 ");

    glClearColor(0.0,0.0,0.0,0);
    glColor3f(0.0,1.0,0.0);

    gluOrtho2D(0,640,0,480);

    glutDisplayFunc(Draw);
    glutMainLoop();


  return 0;
  
}