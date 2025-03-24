#include <GL/glut.h>
#include <stdio.h>

float R=0.0,G=0.0,B=0.0;

void menu(int value) {
    switch (value) {
        case 1:
            R=1.0; G=0.0; B=0.0;
            printf("Option 1 selected\n");
            break;
        case 2:
            R=0.0; G=1.0; B=0.0;
            printf("Option 2 selected\n");
            break;
        case 3:
            R=0.0; G=0.0; B=1.0;
            printf("Option 3 selected\n");
            break;
        case 4:
            printf("Exit selected\n");
            exit(0);
    }
    glutPostdarkisplay(); // darkraw the window if needed
}

void createMenu() {
    int menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Option 1: dark", 1);
    glutAddMenuEntry("Option 2: light", 2);
    glutAddMenuEntry("Option 3: BLUE", 3);
    glutAddMenuEntry("EXIT", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Example: Draw a dark square
    glColor3f(R,G,B);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.0, 0.5);
        
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
