#include <GL/glut.h>
#include <math.h>

float ctrlPoints[4][2];
int pointCount = 0;

void drawBezier() {
    glColor3f(0, 0, 1); // Blue curve
    glBegin(GL_LINE_STRIP);
    for (float u = 0; u <= 1.0; u = u + 0.01) {
        float x = 0, y = 0;

        if (pointCount == 2) {
            // Linear
            x = (1 - u) * ctrlPoints[0][0] + u * ctrlPoints[1][0];
            y = (1 - u) * ctrlPoints[0][1] + u * ctrlPoints[1][1];
        }
        else if (pointCount == 3) {
            // Quadratic
            x = pow(1 - u, 2) * ctrlPoints[0][0]
              + 2 * u * (1 - u) * ctrlPoints[1][0]
              + pow(u, 2) * ctrlPoints[2][0];

            y = pow(1 - u, 2) * ctrlPoints[0][1]
              + 2 * u * (1 - u) * ctrlPoints[1][1]
              + pow(u, 2) * ctrlPoints[2][1];
        }
        else if (pointCount == 4) {
            // Cubic
            x = pow(1 - u, 3) * ctrlPoints[0][0]
              + 3 * u * pow(1 - u, 2) * ctrlPoints[1][0]
              + 3 * pow(u, 2) * (1 - u) * ctrlPoints[2][0]
              + pow(u, 3) * ctrlPoints[3][0];

            y = pow(1 - u, 3) * ctrlPoints[0][1]
              + 3 * u * pow(1 - u, 2) * ctrlPoints[1][1]
              + 3 * pow(u, 2) * (1 - u) * ctrlPoints[2][1]
              + pow(u, 3) * ctrlPoints[3][1];
        }

        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw control points
    glPointSize(5);
    glColor3f(1, 0, 0); // Red
    glBegin(GL_POINTS);
    for (int i = 0; i < pointCount; i++) {
        glVertex2f(ctrlPoints[i][0], ctrlPoints[i][1]);
    }
    glEnd();

    // Draw control lines
    glColor3f(0.6, 0.6, 0.6); // Gray
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < pointCount; i++) {
        glVertex2f(ctrlPoints[i][0], ctrlPoints[i][1]);
    }
    glEnd();

    // Draw Bezier curve if at least 2 points
    if (pointCount >= 2) {
        drawBezier();
    }

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (pointCount < 4) {
            ctrlPoints[pointCount][0] = x;
            ctrlPoints[pointCount][1] = 400 - y; // Flip y-axis
            pointCount++;
        } else {
            // Reset after 4 points
            pointCount = 0;
        }
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Bezier Curve Drawer");
    glClearColor(1, 1, 1, 1); // White background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 400, 0, 400); // 2D coordinates
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
