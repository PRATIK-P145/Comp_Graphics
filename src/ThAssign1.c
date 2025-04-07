#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

int xa = 150, ya = 150, xb = 420, yb = 420, n = 8;
float angle = 0.0;
float xc, yc;
int fillEnabled = 0;

void BresLine(int xa, int ya, int xb, int yb) {
    int dx = abs(xb - xa), dy = abs(yb - ya);
    int sx = (xa < xb) ? 1 : -1;
    int sy = (ya < yb) ? 1 : -1;
    int err = dx - dy;
    while (1) {
        glVertex2i(xa, ya);
        if (xa == xb && ya == yb) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            xa += sx;
        }
        if (e2 < dx) {
            err += dx;
            ya += sy;
        }
    }
}

void BoundaryFill(int x, int y, float fillColor[3], float borderColor[3]) {
    float pixelColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixelColor);
    if ((pixelColor[0] != borderColor[0] || pixelColor[1] != borderColor[1] || pixelColor[2] != borderColor[2]) &&
        (pixelColor[0] != fillColor[0] || pixelColor[1] != fillColor[1] || pixelColor[2] != fillColor[2])) {
        glColor3fv(fillColor);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
        BoundaryFill(x + 1, y, fillColor, borderColor);
        BoundaryFill(x - 1, y, fillColor, borderColor);
        BoundaryFill(x, y + 1, fillColor, borderColor);
        BoundaryFill(x, y - 1, fillColor, borderColor);
    }
}

void rotatePoint(float x, float y, float xc, float yc, float theta, float *x_out, float *y_out) {
    *x_out = xc + (x - xc) * cos(theta) - (y - yc) * sin(theta);
    *y_out = yc + (x - xc) * sin(theta) + (y - yc) * cos(theta);
}

void FillAllSquares(int d, float theta) {
    float dark[3] = {0.0, 0.0, 1.0};
    float light[3] = {1.0, 1.0, 1.0};
    float border[3] = {0.0, 0.0, 0.0};

    for (int row = 0; row < n; row++) {
        for (int i = 0; i < n; i++) {
            float x_center = xa + i * d + d / 2.0;
            float y_center = ya + row * d + d / 2.0;
            float x_rot, y_rot;
            rotatePoint(x_center, y_center, xc, yc, theta, &x_rot, &y_rot);
            if ((i + row) % 2 == 0) {
                BoundaryFill(round(x_rot), round(y_rot), dark, border);
            } else {
                //BoundaryFill(round(x_rot), round(y_rot), light, border);
            }
        }
    }
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    float theta = angle * 3.14159 / 180.0;
    int d = (yb - ya) / n;
    xc = (xa + xb) / 2.0;
    yc = (ya + yb) / 2.0;
    for (int i = 0; i <= n; i++) {
        float x1_rot, y1_rot, x2_rot, y2_rot;
        rotatePoint(xa, ya + i * d, xc, yc, theta, &x1_rot, &y1_rot);
        rotatePoint(xb, ya + i * d, xc, yc, theta, &x2_rot, &y2_rot);
        BresLine(round(x1_rot), round(y1_rot), round(x2_rot), round(y2_rot));
    }
    for (int i = 0; i <= n; i++) {
        float x1_rot, y1_rot, x2_rot, y2_rot;
        rotatePoint(xa + i * d, ya, xc, yc, theta, &x1_rot, &y1_rot);
        rotatePoint(xa + i * d, yb, xc, yc, theta, &x2_rot, &y2_rot);
        BresLine(round(x1_rot), round(y1_rot), round(x2_rot), round(y2_rot));
    }
    glEnd();
    glFlush();
    if (fillEnabled) {
        FillAllSquares(d, theta);
        fillEnabled = 0;
    }
}

void SpecialKeyFunc(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        angle += 5.0;
    } else if (key == GLUT_KEY_RIGHT) {
        angle -= 5.0;
    }
    glutPostRedisplay();
}

void NormalKeyFunc(unsigned char key, int x, int y) {
    if (key == 's' || key == 'S') {
        fillEnabled = 1;
        glutPostRedisplay();
    }
}

void main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Rotating Chessboard with Simultaneous Fill using Boundary Fill");
    glClearColor(1.0, 1.0, 1.0, 0);
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(0, 640, 0, 480);
    glutDisplayFunc(Draw);
    glutSpecialFunc(SpecialKeyFunc);
    glutKeyboardFunc(NormalKeyFunc);
    glutMainLoop();
}