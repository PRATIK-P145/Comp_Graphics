#include <GL/glut.h>

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
    glFlush();                     // Render the content immediately
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);

    // Set display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Set initial window position and size
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);

    // Create the window with a title
    glutCreateWindow("OpenGL GLUT Window");

    // Define the display callback function
    glutDisplayFunc(display);

    // Set the clear color (background color)
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Black background

    // Enter the main loop
    glutMainLoop();

    return 0;
}
