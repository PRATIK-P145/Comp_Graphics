#include <GL/glut.h>
#include <stdio.h>

void menu(int value) {
    switch (value) {
        case 1:
            printf("Option 1 selected\n");
            break;
        case 2:
            printf("Option 2 selected\n");
            break;
        case 3:
            printf("Exit selected\n");
            exit(0);
    }
    glutPostRedisplay(); // Redraw the window if needed
}

void createMenu() {
    int menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Option 1", 1);
    glutAddMenuEntry("Option 2", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Example: Draw a red square
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(-0.5, 0.5);
    glEnd();

    glFlush(); // Ensure all OpenGL commands are executed
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set white background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1); // Set coordinate system
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("GLUT Menu Example");

    init();
    createMenu();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
