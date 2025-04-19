#include <GL/freeglut.h>
#include <cmath>
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 800;
const float PI = 3.14159265358979323846f;

// Draw a simple geometric pattern in the base segment
void drawBasePattern() {
    // Draw a colorful triangle in the base segment
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex2f(0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex2f(0.5f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glVertex2f(0.25f, 0.5f);
    glEnd();

    // Draw some circles
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    for (float r = 0.1f; r <= 0.3f; r += 0.1f) {
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 360; i += 10) {
            float theta = i * PI / 180.0f;
            glVertex2f(r * cos(theta) + 0.3f, r * sin(theta) + 0.2f);
        }
        glEnd();
    }
}

// Apply reflection transformation for kaleidoscope effect
void applyReflection(float angle) {
    glPushMatrix();
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    
    // Reflect across the x-axis (mirror effect)
    glScalef(1.0f, -1.0f, 1.0f);
    
    drawBasePattern();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glLoadIdentity();

    // Set up view to see the whole pattern
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    // Enable stencil buffer for clean edges
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // Draw the original segment (0°)
    drawBasePattern();

    // Draw the reflected segments (120° and 240°)
    applyReflection(120.0f);
    applyReflection(240.0f);

    // Draw boundary lines to visualize segments
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(cos(0), sin(0));
    glVertex2f(0.0f, 0.0f);
    glVertex2f(cos(120.0f * PI / 180.0f), sin(120.0f * PI / 180.0f));
    glVertex2f(0.0f, 0.0f);
    glVertex2f(cos(240.0f * PI / 180.0f), sin(240.0f * PI / 180.0f));
    glEnd();

    glDisable(GL_STENCIL_TEST);
    glutSwapBuffers();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_STENCIL);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("3-Way Kaleidoscope");
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}