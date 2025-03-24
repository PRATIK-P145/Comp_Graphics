#include <stdio.h>
#include<math.h>
#include<GL/glut.h>

int xa,ya,xb,yb;

void Rect(int xa, int ya, int xb, int yb){

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    for(int i=0; i<2; i++){

        glVertex2d(xa,ya);  glVertex2d(xb,ya);
        glVertex2d(xa,yb);  glVertex2d(xb,yb);
        glVertex2d(xa,ya);  glVertex2d(xa,yb);
        glVertex2d(xb,ya);  glVertex2d(xb,yb);

        int mx1,my_1, mx2,my2, mx3,my3, mx4,my4;

        mx1 = (int)(xa+xb)/2;  my_1 = ya;
        mx2 = xb;              my2 = (int)(ya+yb)/2;
        mx3 = (int)(xa+xb)/2;  my3 = yb;
        mx4 = xa;              my4 = (int)(ya+yb)/2;


        glVertex2d(mx1,my_1);  glVertex2d(mx2,my2);
        glVertex2d(mx2,my2);  glVertex2d(mx3,my3);
        glVertex2d(mx3,my3);  glVertex2d(mx4,my4);
        glVertex2d(mx4,my4);  glVertex2d(mx1,my_1);

        xa = (mx1+mx2)/2;  ya = (my_1+my2)/2;
        xb = (mx3+mx4)/2;  yb = (my3+my4)/2;
   }
    // glVertex2d(xa,ya);  glVertex2d(xb,ya);
    // glVertex2d(xa,yb);  glVertex2d(xb,yb);
    // glVertex2d(xa,ya);  glVertex2d(xa,yb);
    // glVertex2d(xb,ya);  glVertex2d(xb,yb);


    glEnd();
    glFlush();

}
void Draw(){
    
    glClear(GL_COLOR_BUFFER_BIT);
    Rect(xa,ya,xb,yb);
    //Rect(100,100,500,300);
}



int main(int argc,char** argv){

    //int xa,ya,xb,yb;
    

    glutInit(&argc , argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow(" HW1 ");

    glClearColor(0.0,0.0,0.0,0);
    glColor3f(0.0,1.0,0.0);

    gluOrtho2D(0,640,0,480);

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

    glutDisplayFunc(Draw);
    glutMainLoop();



  return 0;

}