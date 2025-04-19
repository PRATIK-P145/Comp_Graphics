#include <GL/freeglut.h>
#include <vector>
#include <cmath>

const int WIDTH = 800;
const int HEIGHT = 800;
const float PI = 3.14159265358979323846f;

struct Point {
    float x, y;
    float r, g, b;
};

std::vector<Point> points;
bool isDrawing = false;
float lineWidth = 3.0f;
float currentColor[3] = {1.0f, 0.0f, 0.0f}; // Start with red

// Draw the reflection axes (three lines at 60° angles)
void drawAxes() {
    glColor3f(0.7f, 0.7f, 0.7f);
    glLineWidth(1.0f);
    
    glBegin(GL_LINES);
    // First axis (0°)
    glVertex2f(0.0f, 0.0f);
    glVertex2f(cos(0), sin(0));
    
    // Second axis (60°)
    glVertex2f(0.0f, 0.0f);
    glVertex2f(cos(60.0f * PI / 180.0f), sin(60.0f * PI / 180.0f));
    
    // Third axis (120°)
    glVertex2f(0.0f, 0.0f);
    glVertex2f(cos(120.0f * PI / 180.0f), sin(120.0f * PI / 180.0f));
    glEnd();
}

// Reflect a point across a line at specified angle
Point reflectPoint(const Point& p, float angle) {
    Point reflected;
    float theta = angle * PI / 180.0f;
    
    // Rotation matrix to align axis with x-axis
    float x = p.x * cos(theta) + p.y * sin(theta);
    float y = -p.x * sin(theta) + p.y * cos(theta);
    
    // Reflect across x-axis (now our target line)
    y = -y;
    
    // Rotate back
    reflected.x = x * cos(theta) - y * sin(theta);
    reflected.y = x * sin(theta) + y * cos(theta);
    reflected.r = p.r;
    reflected.g = p.g;
    reflected.b = p.b;
    
    return reflected;
}

void drawPoints() {
    glPointSize(lineWidth);
    
    for (const auto& p : points) {
        glColor3f(p.r, p.g, p.b);
        
        glBegin(GL_POINTS);
        // Original point
        glVertex2f(p.x, p.y);
        
        // First reflection (across 0° axis)
        Point p1 = reflectPoint(p, 0.0f);
        glVertex2f(p1.x, p1.y);
        
        // Second reflection (across 60° axis)
        Point p2 = reflectPoint(p, 60.0f);
        glVertex2f(p2.x, p2.y);
        
        // Third reflection (across 120° axis)
        Point p3 = reflectPoint(p, 120.0f);
        glVertex2f(p3.x, p3.y);
        
        // Reflections of reflections to complete the pattern
        Point p4 = reflectPoint(p1, 60.0f);
        glVertex2f(p4.x, p4.y);
        
        Point p5 = reflectPoint(p1, 120.0f);
        glVertex2f(p5.x, p5.y);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    // Set up view
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    
    drawAxes();
    drawPoints();
    
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDrawing = true;
            
            // Convert window coordinates to OpenGL coordinates
            Point p;
            p.x = (x / (float)WIDTH) * 2.0f - 1.0f;
            p.y = 1.0f - (y / (float)HEIGHT) * 2.0f;
            p.r = currentColor[0];
            p.g = currentColor[1];
            p.b = currentColor[2];
            
            points.push_back(p);
            glutPostRedisplay();
        } else if (state == GLUT_UP) {
            isDrawing = false;
        }
    }
}

void motion(int x, int y) {
    if (isDrawing) {
        Point p;
        p.x = (x / (float)WIDTH) * 2.0f - 1.0f;
        p.y = 1.0f - (y / (float)HEIGHT) * 2.0f;
        p.r = currentColor[0];
        p.g = currentColor[1];
        p.b = currentColor[2];
        
        points.push_back(p);
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case '1': currentColor[0] = 1.0f; currentColor[1] = 0.0f; currentColor[2] = 0.0f; break; // Red
        case '2': currentColor[0] = 0.0f; currentColor[1] = 1.0f; currentColor[2] = 0.0f; break; // Green
        case '3': currentColor[0] = 0.0f; currentColor[1] = 0.0f; currentColor[2] = 1.0f; break; // Blue
        case '4': currentColor[0] = 1.0f; currentColor[1] = 1.0f; currentColor[2] = 0.0f; break; // Yellow
        case '5': currentColor[0] = 1.0f; currentColor[1] = 0.0f; currentColor[2] = 1.0f; break; // Magenta
        case '6': currentColor[0] = 0.0f; currentColor[1] = 1.0f; currentColor[2] = 1.0f; break; // Cyan
        case 'c': points.clear(); glutPostRedisplay(); break; // Clear screen
        case '+': lineWidth += 1.0f; break;
        case '-': if(lineWidth > 1.0f) lineWidth -= 1.0f; break;
    }
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Interactive Kaleidoscope");
    
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    
    return 0;
}