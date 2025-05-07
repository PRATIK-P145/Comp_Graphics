#include <GL/glut.h>
#include<stdio.h>
#include <math.h>
#define PI 3.14159

float t = 0;
float a = PI/12;
int xc = 320, yc = 240;
int r = 100;

float input[3][4] = {};
float rotate[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
float output[3][4] = {};

float rad(int deg){
    return (float)(deg*PI)/180;
}

void init_points(){
    for(int i=0; i<4; i++){
        input[0][i] = xc;
        input[1][i] = yc;
        input[2][i] = 1;
    }
    input[0][0] = xc+r;
    input[0][1] = xc-r;
    input[1][2] = yc+r;
    input[1][3] = yc-r;

    rotate[0][0]= cos(t);   rotate[0][1]= -sin(t);   rotate[0][2]= xc*(1-cos(t))+ yc*sin(t);
    rotate[1][0]= sin(t);   rotate[1][1]=  cos(t);   rotate[1][2]= yc*(1-cos(t))- xc*sin(t);

}

void mul(float inp[3][4], float rot[3][3], float out[3][4]){

    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            out[i][j] = 0;
            for(int k=0; k<3; k++){
                out[i][j] = out[i][j] + ( rot[i][k] * inp[k][j] );
            }
        }
    }
}

void plotCirclePoints(float xc, float yc, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2f(xc + x, yc + y);
    glVertex2f(xc - x, yc + y);
    glVertex2f(xc + x, yc - y);
    glVertex2f(xc - x, yc - y);
    glVertex2f(xc + y, yc + x);
    glVertex2f(xc - y, yc + x);
    glVertex2f(xc + y, yc - x);
    glVertex2f(xc - y, yc - x);
    glEnd();
}
void BresCircle(float xc, float yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    while (x <= y) {
        plotCirclePoints(xc, yc, x, y);
        glFlush();
    if (d < 0) {
        d = d + 4 * x + 6;
    } else {
        d = d + 4 * (x - y) + 15;
        y--;
    }
      x++;
    }
   
}

void draw_circles( float arr[3][4], int radius){
    for(int i=0; i<4; i++){
        BresCircle(arr[0][i],arr[1][i],radius);
    }
}

void MouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
         xc = x;
         yc = 480-y;
        
// printf("Clicked at point %d, %d", xc, yc);
    }
}

void keypress(int key, int x, int y){
    if (key == GLUT_KEY_LEFT) {
        t += a;
    } else if (key == GLUT_KEY_RIGHT) {
        t -= a;
    }
    glutPostRedisplay();
}

void display() {
    
    glClear(GL_COLOR_BUFFER_BIT);
    //glColor3f(1, 0, 0);
    //BresCircle(xc, yc, r);
    init_points();

    glPointSize(1.0);
    glColor3f(0, 0, 1);
    draw_circles(input, r);
    // BresCircle(xc+r, yc, r);
    // BresCircle(xc-r, yc, r);
    // BresCircle(xc, yc+r, r);
    // BresCircle(xc, yc-r, r);
    // glFlush();
    mul(input, rotate, output);

    // for(int i=0; i<3 ; i++){
    //     for(int j=0; j<4; j++){
    //         printf("%f ",output[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    glPointSize(2.0);
    glColor3f(0,0,0);
    draw_circles(output,r);


}
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Theory Assign : Q.14");

    glClearColor(1.0, 1.0, 1.0, 0);
    glColor3f(0.0, 1.0, 0.0);

    gluOrtho2D(0,640,0,480);

    glutDisplayFunc(display);
    glutMouseFunc(MouseClick);
    glutSpecialFunc(keypress);

    glutMainLoop();

    return 0;
}