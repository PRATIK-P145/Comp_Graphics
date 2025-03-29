#include <GL/glut.h>
#include <iostream>

using namespace std;

// Window dimensions
const int WIDTH = 500, HEIGHT = 500;

// Position and size of squares
const float squareSize = 20.0f;
const float squareY = 450.0f; // Near the top

// Mouse position
int mouseX, mouseY;

// Selected color
float selectedColor[3] = {0.0f, 0.0f, 0.0f}; // Default WHITE

// Draw the squares at the top
void drawSquares() {
    // RED square
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(50.0f, squareY);
    glVertex2f(50.0f + squareSize, squareY);
    glVertex2f(50.0f + squareSize, squareY - squareSize);
    glVertex2f(50.0f, squareY - squareSize);
    glEnd();

    // BLUE square
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(120.0f, squareY);
    glVertex2f(120.0f + squareSize, squareY);
    glVertex2f(120.0f + squareSize, squareY - squareSize);
    glVertex2f(120.0f, squareY - squareSize);
    glEnd();

    // GREEN square
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(190.0f, squareY);
    glVertex2f(190.0f + squareSize, squareY);
    glVertex2f(190.0f + squareSize, squareY - squareSize);
    glVertex2f(190.0f, squareY - squareSize);
    glEnd();
}

// Draw the triangle with the selected color
void drawTriangle() {
    glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
    glBegin(GL_TRIANGLES);
    glVertex2f(250.0f, 200.0f);
    glVertex2f(200.0f, 100.0f);
    glVertex2f(300.0f, 100.0f);
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawSquares();  // Draw the colored squares
    drawTriangle(); // Draw the triangle

    glFlush();
}

// Track mouse motion
void motionFunc(int x, int y) {
    mouseX = x;
    mouseY = HEIGHT - y; // Invert y-axis to match OpenGL coordinates
    cout<<"(x,y) : "<<x<<" , "<<mouseY<<endl;
    
}

// Mouse click handler
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Check if cursor is inside the RED square
        if (x >= 50 && x <= 50 + squareSize && mouseY <= squareY - squareSize && mouseY >= squareY) {
            selectedColor[0] = 1.0f; // RED
            selectedColor[1] = 0.0f;
            selectedColor[2] = 0.0f;
        }
        // Check if cursor is inside the BLUE square
        else if (x >= 120 && x <= 120 + squareSize && mouseY >= squareY - squareSize && mouseY <= squareY) {
            selectedColor[0] = 0.0f;
            selectedColor[1] = 0.0f;
            selectedColor[2] = 1.0f; // BLUE
        }
        // Check if cursor is inside the GREEN square
        else if (x >= 190 && x <= 190 + squareSize && mouseY >= squareY - squareSize && mouseY <= squareY) {
            selectedColor[0] = 0.0f;
            selectedColor[1] = 1.0f; // GREEN
            selectedColor[2] = 0.0f;
        }
    }
    glutPostRedisplay(); // Redraw with the selected color
}

// Initialize OpenGL
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set background to white
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT); // Define 2D coordinate system
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Color Selection and Triangle Drawing");

    init();

    glutDisplayFunc(display);
    glutMotionFunc(motionFunc);
    glutMouseFunc(mouseClick);

    glutMainLoop();
    return 0;
}
