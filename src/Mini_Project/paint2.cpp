// Basic 2D Paint App Template with OpenGL + FreeGLUT
// Features: Color buttons (R, G, B), Circle and Rectangle tool, Eraser with size selector

#include <GL/freeglut.h>
#include <vector>
#include<math.h>
#include <string>

// Tool identifiers
enum Tool { NONE, RECTANGLE, CIRCLE, ERASER };

int windowWidth = 800, windowHeight = 600;
Tool currentTool = NONE;
float currentColor[3] = {1.0f, 0.0f, 0.0f}; // Default Red
int eraserSize = 10;
bool isDrawing = false;
int startX, startY, endX, endY;

// Draw UI buttons
void drawButton(int x, int y, int w, int h, const char* label, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + w, y);
    glVertex2i(x + w, y + h);
    glVertex2i(x, y + h);
    glEnd();

    glColor3f(1, 1, 1);
    glRasterPos2i(x + 5, y + h / 2);
    for (int i = 0; label[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[i]);
}

void drawUI() {
    drawButton(10, 550, 60, 30, "Red", 1, 0, 0);
    drawButton(80, 550, 60, 30, "Green", 0, 1, 0);
    drawButton(150, 550, 60, 30, "Blue", 0, 0, 1);
    drawButton(220, 550, 80, 30, "Circle", 0.5, 0.5, 0.5);
    drawButton(310, 550, 100, 30, "Rectangle", 0.5, 0.5, 0.5);
    drawButton(420, 550, 80, 30, "Eraser", 0.8, 0.8, 0.8);
}

void drawPreviewShape() {
    if (!isDrawing) return;
    glColor3fv(currentColor);
    if (currentTool == RECTANGLE) {
        glBegin(GL_LINE_LOOP);
        glVertex2i(startX, startY);
        glVertex2i(endX, startY);
        glVertex2i(endX, endY);
        glVertex2i(startX, endY);
        glEnd();
    } else if (currentTool == CIRCLE) {
        float cx = (startX + endX) / 2.0f;
        float cy = (startY + endY) / 2.0f;
        float rx = abs(endX - startX) / 2.0f;
        float ry = abs(endY - startY) / 2.0f;
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 100; ++i) {
            float theta = 2.0f * 3.1415926f * float(i) / 100;
            glVertex2f(cx + cos(theta) * rx, cy + sin(theta) * ry);
        }
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawUI();
    drawPreviewShape();
    glutSwapBuffers();
}

void mouseClick(int button, int state, int x, int y) {
    y = windowHeight - y; // Flip Y axis
    if (state == GLUT_DOWN) {
        if (y > 550) { // UI Area
            if (x >= 10 && x <= 70) { currentColor[0] = 1; currentColor[1] = 0; currentColor[2] = 0; }
            else if (x >= 80 && x <= 140) { currentColor[0] = 0; currentColor[1] = 1; currentColor[2] = 0; }
            else if (x >= 150 && x <= 210) { currentColor[0] = 0; currentColor[1] = 0; currentColor[2] = 1; }
            else if (x >= 220 && x <= 300) currentTool = CIRCLE;
            else if (x >= 310 && x <= 410) currentTool = RECTANGLE;
            else if (x >= 420 && x <= 500) currentTool = ERASER;
        } else {
            isDrawing = true;
            startX = endX = x;
            startY = endY = y;
        }
    } else if (state == GLUT_UP) {
        isDrawing = false;
        if (currentTool == ERASER) {
            glColor3f(1, 1, 1);
            glBegin(GL_QUADS);
            glVertex2i(x - eraserSize, y - eraserSize);
            glVertex2i(x + eraserSize, y - eraserSize);
            glVertex2i(x + eraserSize, y + eraserSize);
            glVertex2i(x - eraserSize, y + eraserSize);
            glEnd();
        }
    }
    glutPostRedisplay();
}

void motion(int x, int y) {
    y = windowHeight - y;
    endX = x;
    endY = y;
    glutPostRedisplay();
}

void init() {
    glClearColor(1, 1, 1, 1); // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("2D Paint App - Basic Template");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;
}
