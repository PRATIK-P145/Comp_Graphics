#include <GL/glut.h>

void DrawPoint(float x, float y) {
    glPointSize(3.0); // Set point size
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
    glFlush();
}

void MouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float normalizedX = x;          // Normalize x to match OpenGL's coordinates
        float normalizedY = 480-y; // Invert y (OpenGL's origin is bottom-left)
        DrawPoint(normalizedX, normalizedY);
    }
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Mouse Interaction Example");

    glClearColor(0.0, 0.0, 0.0, 0.0); // Black background
    glColor3f(0.0, 1.0, 0.0);         // dark color for points
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);   // Define coordinate system

    glutDisplayFunc(Display);
    glutMouseFunc(MouseClick);        // Register mouse click callback

    glutMainLoop();
    return 0;
}
