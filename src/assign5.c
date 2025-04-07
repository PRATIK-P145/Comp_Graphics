#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

float backcol[3];
float bcol[3];
float fcol[3];
int input[2][15];
int v, x, y, xa, ya, xb, yb, ch;

void Bfill(int x, int y, float bcol[3], float fcol[3]) {
    float current[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, current);

    if ((current[0] != bcol[0] || current[1] != bcol[1] || current[2] != bcol[2]) &&
        (current[0] != fcol[0] || current[1] != fcol[1] || current[2] != fcol[2])) {
        glColor3f(fcol[0], fcol[1], fcol[2]);
        glBegin(GL_POINTS);
        glVertex2d(x, y);
        glEnd();
        glFlush();

        Bfill(x + 1, y, bcol, fcol);
        Bfill(x - 1, y, bcol, fcol);
        Bfill(x, y + 1, bcol, fcol);
        Bfill(x, y - 1, bcol, fcol);
    }
}

void floodFill(int x, int y, float fcol[3], float backcol[3]) {
    float current[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, current);

    if ((current[0] == backcol[0] && current[1] == backcol[1] && current[2] == backcol[2]) &&
        (current[0] != fcol[0] || current[1] != fcol[1] || current[2] != fcol[2])) {
        glColor3f(fcol[0], fcol[1], fcol[2]);
        glBegin(GL_POINTS);
        glVertex2d(x, y);
        glEnd();
        glFlush();

        floodFill(x + 1, y, fcol, backcol);
        floodFill(x - 1, y, fcol, backcol);
        floodFill(x, y + 1, fcol, backcol);
        floodFill(x, y - 1, fcol, backcol);
    }
}

int Round(float a) {
    return (int)(a + 0.5);
}

void DDA(int xa, int ya, int xb, int yb) {
    int dx, dy, steps;
    dx = xb - xa;
    dy = yb - ya;

    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
    } else {
        steps = abs(dy);
    }

    float xinc, yinc;
    float x = xa, y = ya;
    xinc = (float)dx / steps;
    yinc = (float)dy / steps;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2d(Round(x), Round(y));
        x += xinc;
        y += yinc;
    }
    glEnd();
    glFlush();
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(bcol[0], bcol[1], bcol[2]);
    
    int i;
    for (i = 0; i < v - 1; i++) {
        DDA(input[0][i], input[1][i], input[0][i + 1], input[1][i + 1]);
    }
    DDA(input[0][i], input[1][i], input[0][0], input[1][0]);
}

void mouse(int button, int state, int mx, int my) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int windowheight = glutGet(GLUT_WINDOW_HEIGHT);
        y = windowheight - my;  // Invert Y-axis for OpenGL coordinates
        x = mx;
    }

    int xmin = input[0][0], xmax = input[0][0];
    int ymin = input[1][0], ymax = input[1][0];

    for (int i = 1; i < v; i++) {
        if (input[0][i] < xmin) xmin = input[0][i];
        if (input[0][i] > xmax) xmax = input[0][i];
        if (input[1][i] < ymin) ymin = input[1][i];
        if (input[1][i] > ymax) ymax = input[1][i];
    }

    if (x >= xmin && x <= xmax && y >= ymin && y <= ymax) {
        switch (ch) {
            case 1:
                Bfill(x, y, bcol, fcol);
                break;

            case 2:
                floodFill(x, y, fcol, backcol);
                break;
        }
    }
}

int main(int argc, char **argv) {
    printf("\n1. Boundary Fill\n2. Flood Fill\nSelect an Option: ");
    scanf("%d", &ch);
    printf("\nEnter number of Vertices: ");
    scanf("%d", &v);

    for (int i = 0; i < v; i++) {
        printf("\nX[%d]: ", i + 1);
        scanf("%d", &input[0][i]);

        printf("\nY[%d]: ", i + 1);
        scanf("%d", &input[1][i]);
    }

    for (int i = 0; i < 3; i++) {
        printf("\nEnter Fill Color[%d]: ", i);
        scanf("%f", &fcol[i]);
    }

    for (int i = 0; i < 3; i++) {
        printf("\nEnter Boundary Color[%d]: ", i);
        scanf("%f", &bcol[i]);
    }

    for (int i = 0; i < 3; i++) {
        printf("\nEnter Background Color[%d]: ", i);
        scanf("%f", &backcol[i]);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Assign-5 : Polygon Fill");
    glClearColor(backcol[0], backcol[1], backcol[2], 0);
    gluOrtho2D(0, 640, 0, 480);
    glutDisplayFunc(Draw);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
