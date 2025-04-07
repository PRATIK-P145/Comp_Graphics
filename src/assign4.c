#include <GL/glut.h>
#include <math.h>

const int windowWidth = 640, windowHeight = 480;
const int radius = 150;


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


void BresCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        plotCirclePoints(xc, yc, x, y);
        x++;

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            y--;
            d = d + 4 * (x - y) + 15;
        }
    }
}


void drawSquare(int xc, int yc, int side) {
    int half = side / 2;

    glBegin(GL_LINE_LOOP);
    glVertex2i(xc - half, yc - half);
    glVertex2i(xc + half, yc - half);
    glVertex2i(xc + half, yc + half);
    glVertex2i(xc - half, yc + half);
    glEnd();
}


void drawObject(int xc, int yc, int r, int side) {
  
    drawSquare(xc + r, yc + r, side); 
    drawSquare(xc - r, yc + r, side); 
    drawSquare(xc - r, yc - r, side);
    drawSquare(xc + r, yc - r, side); 
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    

    int xc = windowWidth / 2;
    int yc = windowHeight / 2;
    int side = 40;


    glColor3f(0.0, 0.0, 0.0);
    BresCircle(xc, yc, radius);

   
    glColor3f(0.0, 0.0, 1.0); 
    drawObject(xc, yc, radius, side);

    glFlush();
}


void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Assign-4 : Bresnum Circle");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
