#include <GL/glut.h>
#include <stdio.h>

// Globals
int startX, startY, endX, endY;
int clickCount = 0;
int lineStyle = 0; // 0-Simple, 1-Dashed, 2-Dotted, 3-DashDotted

// Convert screen coordinates to OpenGL center-based
int convertX(int x) { return x - 250; }
int convertY(int y) { return 250 - y; }

// Function to draw pixel with OpenGL
void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Bresenham’s Line Drawing with styles
void drawBresenham(int x1, int y1, int x2, int y2, int style) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x2 > x1) ? 1 : -1;
    int sy = (y2 > y1) ? 1 : -1;
    int err = dx - dy, count = 0;

    while (1) {
        // Style logic
        switch (style) {
            case 0: drawPixel(x1, y1); break; // Simple
            case 1: if (count % 10 < 6) drawPixel(x1, y1); break; // Dashed (6 on, 4 off)
            case 2: if (count % 6 == 0) drawPixel(x1, y1); break; // Dotted (1 on, 5 off)
            case 3: if ((count % 15 < 6) || (count % 15 == 8)) drawPixel(x1, y1); break; // Dash-Dotted
        }

        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx)  { err += dx; y1 += sy; }
        count++;
    }
    glFlush();
}

// Draw quadrants
void drawAxes() {
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2i(-250, 0); glVertex2i(250, 0); // X-axis
    glVertex2i(0, -250); glVertex2i(0, 250); // Y-axis
    glEnd();
}

// Mouse click callback
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (clickCount == 0) {
            startX = convertX(x);
            startY = convertY(y);
            clickCount = 1;
        } else {
            endX = convertX(x);
            endY = convertY(y);
            drawBresenham(startX, startY, endX, endY, lineStyle);
            clickCount = 0;
        }
    }
}

// Menu callback
void menu(int option) {
    lineStyle = option;
}

// Display function
void display() { 
    drawAxes(); // Draw quadrant lines
    glFlush();
}

// Initialization
void init() {
    glClearColor(0, 0, 0, 1); // Black background
    glColor3f(0, 1, 0);       // Green lines
    gluOrtho2D(-250, 250, -250, 250); // Set coordinate system
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Line Styles with Mouse");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);

    // Create right-click menu
    glutCreateMenu(menu);
    glClear(GL_COLOR_BUFFER_BIT);
    glutAddMenuEntry("Simple Line", 0);
    glutAddMenuEntry("Dashed Line", 1);
    glutAddMenuEntry("Dotted Line", 2);
    glutAddMenuEntry("Dash-Dotted Line", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
	return	0;
}
