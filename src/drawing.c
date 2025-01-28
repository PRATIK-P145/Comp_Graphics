#include <GL/glut.h>

float startX, startY; // Starting position of the line
int isDragging = 0;

void MouseClick(int button, int state, int x, int y) {
    float normalizedX = x;
    float normalizedY = (480 - y) ;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        startX = normalizedX;
        startY = normalizedY;
        isDragging = 1;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        isDragging = 0;
    }
}

void MouseMotion(int x, int y) {
    if (isDragging) {
        float endX = x ;
        float endY = (480 - y) ;

        glBegin(GL_LINES);
            glVertex2f(startX, startY);
           
            glVertex2f(endX, endY);
        glEnd();
        glFlush();

        //startX = endX;
        //startY = endY;
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
    glutCreateWindow("Mouse Drag Example");

    glClearColor(0.0, 0.0, 0.0, 0.0); // Black background
    glColor3f(0.0, 1.0, 0.0);         // Green color for lines
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);

    glutDisplayFunc(Display);
    glutMouseFunc(MouseClick);        // Register mouse click callback
    glutMotionFunc(MouseMotion);      // Register mouse motion callback

    glutMainLoop();
    return 0;
}
