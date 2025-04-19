#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#define M_PI 3.14159265358979323846

float sec[3][2] = {{0, 0}, {100, 200}, {1, 1}};
float secop[3][2];
float min[3][2] = {{0, 0}, {100, 175}, {1, 1}};
float minop[3][2];
float hour[3][2] = {{0, 0}, {100, 150}, {1, 1}};
float hourop[3][2];
float r[3][3];

float line[3][2] = {{0, 0}, {-50, -220}, {1, 1}};
float lineop[3][2];
float arc[3][2] = {{0, 0}, {230, 250}, {1, 1}};
float arcop[3][2];
float arcs[3][2] = {{0, 0}, {242, 250}, {1, 1}};
float arcsop[3][2];

int Round(float a) {
    return (int)(a + 0.5);
}

void DDAl(int xa, int ya, int xb, int yb) {
    int dx = xb - xa;
    int dy = yb - ya;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    float xin = (float)(dx) / steps;
    float yin = (float)(dy) / steps;
    float x = xa, y = ya;

    glVertex2d(xa, ya);
    for (int i = 0; i < steps; i++) {
        x += xin;
        y += yin;
        glVertex2d(Round(x), Round(y));
    }
}

void mul(float output[3][2], float r[3][3], float input[3][2]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            output[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                output[i][j] += r[i][k] * input[k][j];
            }
        }
    }
}

void Rotation(float hand[3][2], float angle, float handop[3][2]) {
    float rad = angle * M_PI / 180;
    int xf = 0, yf = 100;

    r[0][0] = cos(rad);
    r[0][1] = -sin(rad);
    r[0][2] = xf * (1 - cos(rad)) + yf * sin(rad);
    r[1][0] = sin(rad);
    r[1][1] = cos(rad);
    r[1][2] = yf * (1 - cos(rad)) - xf * sin(rad);
    r[2][0] = 0;
    r[2][1] = 0;
    r[2][2] = 1;

    mul(handop, r, hand);
}

void rpendulum(float hand[3][2], float angle, float handop[3][2]) {
    float rad = angle * M_PI / 180;
    int xf = 0, yf = -50;

    r[0][0] = cos(rad);
    r[0][1] = -sin(rad);
    r[0][2] = xf * (1 - cos(rad)) + yf * sin(rad);
    r[1][0] = sin(rad);
    r[1][1] = cos(rad);
    r[1][2] = yf * (1 - cos(rad)) - xf * sin(rad);
    r[2][0] = 0;
    r[2][1] = 0;
    r[2][2] = 1;

    mul(handop, r, hand);
}

void BCIR(int xc, int yc, int r) {
    int x = 0, y = r, d = 3 - 2 * r;
    do {
        glVertex2d(xc + x, yc + y);
        glVertex2d(xc + y, yc + x);
        glVertex2d(xc - x, yc + y);
        glVertex2d(xc + y, yc - x);
        glVertex2d(xc + x, yc - y);
        glVertex2d(xc - y, yc + x);
        glVertex2d(xc - x, yc - y);
        glVertex2d(xc - y, yc - x);

        if (d < 0) {
            x += 1;
            d += 4 * x + 6;
        } else {
            x += 1;
            y -= 1;
            d += 4 * x - 4 * y + 10;
        }
    } while (y >= x);
}

void Draw() {
    int z = 0;
    while (1) {
        z++;
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1, 1, 1);

        glPointSize(2.0f);
        glBegin(GL_POINTS);
        for (int i = 0; i < 12; i++) {
            DDAl(arc[0][0], arc[1][0], arc[0][1], arc[1][1]);
            Rotation(arc, -30, arcop);
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 2; j++)
                    arc[i][j] = arcop[i][j];
        }
        glEnd();

        glPointSize(1.0f);
        glBegin(GL_POINTS);
        for (int i = 0; i < 60; i++) {
            DDAl(arcs[0][0], arcs[1][0], arcs[0][1], arcs[1][1]);
            Rotation(arcs, -6, arcsop);
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 2; j++)
                    arcs[i][j] = arcsop[i][j];
        }
        glEnd();

        glPointSize(2.0f);
        glBegin(GL_POINTS);
        BCIR(0, 100, 150);
        glEnd();

        glPointSize(1.0f);
        glBegin(GL_POINTS);
        DDAl(sec[0][0], sec[1][0], sec[0][1], sec[1][1]);
        glEnd();

        glPointSize(2.0f);
        glBegin(GL_POINTS);
        DDAl(min[0][0], min[1][0], min[0][1], min[1][1]);
        glEnd();

        glPointSize(3.0f);
        glBegin(GL_POINTS);
        DDAl(hour[0][0], hour[1][0], hour[0][1], hour[1][1]);
        glEnd();

        glPointSize(4.0f);
        glBegin(GL_POINTS);
        DDAl(line[0][0], line[1][0], line[0][1], line[1][1]);
        glEnd();

        glPointSize(1.0f);
        glBegin(GL_POINTS);
        float pend = cos(z * M_PI * (0.02 / 2));
        rpendulum(line, pend, lineop);
        glEnd();

        glBegin(GL_POLYGON);
        BCIR(line[0][1], line[1][1], 20);
        glEnd();

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 2; j++)
                line[i][j] = lineop[i][j];

        if (z % 100 == 0) {
            Rotation(sec, -6, secop);
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 2; j++)
                    sec[i][j] = secop[i][j];
        }

        if (z % 6000 == 0) {
            Rotation(min, -6, minop);
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 2; j++)
                    min[i][j] = minop[i][j];
        }

        if (z % 72000 == 0) {
            Rotation(hour, -6, hourop);
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 2; j++)
                    hour[i][j] = hourop[i][j];
        }

        glFlush();
        Sleep(10); // Can be uncommented to control animation speed
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(700, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("CLOCK");

    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    gluOrtho2D(-300, 300, -300, 300);

    glutDisplayFunc(Draw);
    glutMainLoop();

    return 0;
}
