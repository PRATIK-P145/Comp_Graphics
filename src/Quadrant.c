#include <stdio.h>
#include<math.h>
#include<GL/glut.h>

int xa,ya,xb,yb;

void Draw(){
    
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(3.0);
    glBegin(GL_LINES);
        glVertex2d(0,-230);
        glVertex2d(0,230);

        glVertex2d(-310,0);
        glVertex2d(310,0);

    glEnd();
    glFlush();
   // 
    //Rect(100,100,500,300);
}



int main(int argc,char** argv){

    //int xa,ya,xb,yb;
    printf("Enter Co-ordinates of Bottom-Left Vertex ->\n");
    printf(" X1 :");
    scanf("%d",&xa);
    printf(" Y1 :");
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
    glutCreateWindow(" Draw ");

    glClearColor(0.0,0.0,0.0,0);
    glColor3f(0.0,1.0,0.0);

    gluOrtho2D(-320,320,-240,240);

    glutDisplayFunc(Draw);
    glutMainLoop();


  return 0;

}