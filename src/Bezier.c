#include <stdio.h>
#include<GL/freeglut.h>
#include<math.h>

int ctrlpoint[2][4] = {};
int count = 0;

void draw_Bezier(){
    float x = 0, y = 0;
    glBegin(GL_LINE_STRIP);
    for(float u=0.0; u<=1.0; u += 0.01 ){

        if(count == 2){
            x = (1-u)*ctrlpoint[0][0] + u*ctrlpoint[0][1];
            y = (1-u)*ctrlpoint[1][0] + u*ctrlpoint[1][1];
        }
        else if(count==3){
             x = pow((1-u),2)*ctrlpoint[0][0] + 2*u*(1-u)*ctrlpoint[0][1] + u*u*ctrlpoint[0][2];
             y = pow((1-u),2)*ctrlpoint[1][0] + 2*u*(1-u)*ctrlpoint[1][1] + u*u*ctrlpoint[1][2];
        }
        else if(count==4){
             x = pow((1-u),3)*ctrlpoint[0][0] + 3*u*pow((1-u),2)*ctrlpoint[0][1] + 3*pow(u,2)*(1-u)*ctrlpoint[0][2] + pow(u,3)*ctrlpoint[0][3];
             y = pow((1-u),3)*ctrlpoint[1][0] + 3*u*pow((1-u),2)*ctrlpoint[1][1] + 3*pow(u,2)*(1-u)*ctrlpoint[1][2] + pow(u,3)*ctrlpoint[1][3];  
        }
        glVertex2d(x,y);
    }
    glEnd();
    
}

void mouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(count<4){
            ctrlpoint[0][count] = x;
            ctrlpoint[1][count] = 480-y;
            count++;
        }else{
            count = 0;
        }
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(5.0);
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
    for(int i=0; i<count; i++){
        glVertex2d(ctrlpoint[0][i],ctrlpoint[1][i]);
    }
    glEnd();

    glColor3f(0,0,1);
    glBegin(GL_LINE_STRIP);
    for(int i=0; i<count; i++){
        glVertex2d(ctrlpoint[0][i],ctrlpoint[1][i]);
    }
    glEnd();

    glColor3f(0,1,0);
    if(count>1){
        draw_Bezier();
    }
    glFlush();
}

void main(int argc, char** argv ){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("Bezier Curve");

    glClearColor(0,0,0,0);
    glColor3f(0,1,0);

    gluOrtho2D(0,640,0,480);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();

    return ;
}