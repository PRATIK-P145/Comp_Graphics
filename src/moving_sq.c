#include <GL/glut.h>

float x_pos = -50.0;  // Initial X position of square
int direction = 1;    // 1 = move right, -1 = move left

void drawSquare(float x, float y) {
    glBegin(GL_QUADS);
        glVertex2f(x - 15, y - 15);
        glVertex2f(x + 15, y - 15);
        glVertex2f(x + 15, y + 15);
        glVertex2f(x - 15, y + 15);
    glEnd();
}

// Function to update square position
void update() {
    x_pos += direction * 0.1;  // Update X position

    // Change direction if boundary is hit
    if (x_pos > 50.0 || x_pos < -50.0) {
        direction *= -1;
    }

    glutPostRedisplay();  // Re-trigger display function
}

// Function to draw the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 1.0, 0.0);  // Green square
    drawSquare(x_pos, 0.0);

    x_pos += direction * 0.1;  // Update X position

    // Change direction if boundary is hit
    if (x_pos > 50.0 || x_pos < -50.0) {
        direction *= -1;
    }

    glFlush();
}

// Main function to set up GLUT
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(150, 150);

    glutCreateWindow("Square Moving with glutIdleFunc");

    glClearColor(0.0, 0.0, 0.0, 1.0);  // Background color
    gluOrtho2D(-150, 150, -150, 150);

    glutDisplayFunc(display);     // Register display callback
    //glutIdleFunc(update);         // Register idle callback

    glutMainLoop();  // Start the GLUT main loop
    return 0;
}
