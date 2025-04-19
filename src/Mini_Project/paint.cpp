#include <GL/freeglut.h>
#include <vector>
#include <stack>
#include <math.h>
#include<stdio.h>
#include <algorithm>
#include <string>

// Canvas dimensions
const int WIDTH = 1000;
const int HEIGHT = 700;
const int GUI_PANEL_WIDTH = 200;

// Drawing tools enum
enum Tool {
    PENCIL,
    LINE,
    RECTANGLE,
    CIRCLE,
    ERASER,
    FILL,
    COLOR_PICKER
};

// Current tool and color
Tool currentTool = PENCIL;
float currentColor[3] = { 0.0f, 0.0f, 0.0f }; // Black by default
float bgColor[3] = { 1.0f, 1.0f, 1.0f }; // White background

// Drawing state variables
bool isDrawing = false;
int startX, startY;
int prevX, prevY;

// GUI state
bool showGUI = true;
int hoveredButton = -1;
int selectedColor = -1;

// Canvas data
std::vector<std::vector<float>> canvas(WIDTH - GUI_PANEL_WIDTH, std::vector<float>(HEIGHT * 3));
std::stack<std::vector<std::vector<float>>> undoStack;
std::stack<std::vector<std::vector<float>>> redoStack;

// Tool information
struct ToolInfo {
    std::string name;
    char shortcut;
    float color[3];
};

ToolInfo tools[] = {
    {"Pencil", 'p', {0.2f, 0.2f, 0.2f}},
    {"Line", 'l', {0.8f, 0.0f, 0.0f}},
    {"Rectangle", 'r', {0.0f, 0.5f, 0.0f}},
    {"Circle", 'c', {0.0f, 0.0f, 0.8f}},
    {"Eraser", 'e', {0.7f, 0.7f, 0.7f}},
    {"Fill", 'f', {0.5f, 0.0f, 0.5f}},
    {"Color Picker", 'k', {0.0f, 0.8f, 0.8f}}
};

// Color palette
float colors[][3] = {
    {0.0f, 0.0f, 0.0f}, // Black
    {1.0f, 0.0f, 0.0f}, // Red
    {0.0f, 1.0f, 0.0f}, // Green
    {0.0f, 0.0f, 1.0f}, // Blue
    {1.0f, 1.0f, 0.0f}, // Yellow
    {1.0f, 0.0f, 1.0f}, // Magenta
    {0.0f, 1.0f, 1.0f}, // Cyan
    {1.0f, 1.0f, 1.0f}, // White
    {0.5f, 0.5f, 0.5f}, // Gray
    {0.5f, 0.0f, 0.0f}, // Dark Red
    {0.0f, 0.5f, 0.0f}, // Dark Green
    {0.0f, 0.0f, 0.5f}  // Dark Blue
};
const int NUM_COLORS = sizeof(colors) / sizeof(colors[0]);

// Initialize canvas with background color
void initCanvas() {
    for (int x = 0; x < WIDTH - GUI_PANEL_WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            canvas[x][y * 3] = bgColor[0];     // R
            canvas[x][y * 3 + 1] = bgColor[1]; // G
            canvas[x][y * 3 + 2] = bgColor[2]; // B
        }
    }
}

// Save current canvas state to undo stack
void saveState() {
    undoStack.push(canvas);
    // Clear redo stack when making a new change
    while (!redoStack.empty()) {
        redoStack.pop();
    }
}

// Undo action
void undo() {
    if (!undoStack.empty()) {
        redoStack.push(canvas);
        canvas = undoStack.top();
        undoStack.pop();
        glutPostRedisplay();
    }
}

// Redo action
void redo() {
    if (!redoStack.empty()) {
        undoStack.push(canvas);
        canvas = redoStack.top();
        redoStack.pop();
        glutPostRedisplay();
    }
}

// Draw a point on canvas
void drawPoint(int x, int y) {
    if (x >= 0 && x < WIDTH - GUI_PANEL_WIDTH && y >= 0 && y < HEIGHT) {
        if (currentTool == ERASER) {
            canvas[x][y * 3] = bgColor[0];
            canvas[x][y * 3 + 1] = bgColor[1];
            canvas[x][y * 3 + 2] = bgColor[2];
        } else {
            canvas[x][y * 3] = currentColor[0];
            canvas[x][y * 3 + 1] = currentColor[1];
            canvas[x][y * 3 + 2] = currentColor[2];
        }
    }
}

// Draw a line using Bresenham's algorithm
void drawLine(int x0, int y0, int x1, int y1) {
    bool steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = abs(y1 - y0);
    int error = dx / 2;
    int ystep = (y0 < y1) ? 1 : -1;
    int y = y0;

    for (int x = x0; x <= x1; x++) {
        if (steep) {
            drawPoint(y, x);
        } else {
            drawPoint(x, y);
        }
        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}

// Draw a rectangle
void drawRectangle(int x0, int y0, int x1, int y1) {
    drawLine(x0, y0, x1, y0);
    drawLine(x1, y0, x1, y1);
    drawLine(x1, y1, x0, y1);
    drawLine(x0, y1, x0, y0);
}

// Draw a circle using midpoint algorithm
void drawCircle(int xc, int yc, int radius) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (y >= x) {
        drawPoint(xc + x, yc + y);
        drawPoint(xc - x, yc + y);
        drawPoint(xc + x, yc - y);
        drawPoint(xc - x, yc - y);
        drawPoint(xc + y, yc + x);
        drawPoint(xc - y, yc + x);
        drawPoint(xc + y, yc - x);
        drawPoint(xc - y, yc - x);

        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
        x++;
    }
}

// Flood fill algorithm
void floodFill(int x, int y, const float oldColor[3], const float newColor[3]) {
    if (x < 0 || x >= WIDTH - GUI_PANEL_WIDTH || y < 0 || y >= HEIGHT) return;
    
    float pixel[3] = {
        canvas[x][y * 3],
        canvas[x][y * 3 + 1],
        canvas[x][y * 3 + 2]
    };
    
    if (pixel[0] == oldColor[0] && pixel[1] == oldColor[1] && pixel[2] == oldColor[2]) {
        drawPoint(x, y);
        
        floodFill(x + 1, y, oldColor, newColor);
        floodFill(x - 1, y, oldColor, newColor);
        floodFill(x, y + 1, oldColor, newColor);
        floodFill(x, y - 1, oldColor, newColor);
    }
}

// Draw text on screen
void drawText(float x, float y, const std::string &text) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
}

// Draw the GUI panel
void drawGUI() {
    if (!showGUI) return;

    // Draw GUI background
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2i(WIDTH - GUI_PANEL_WIDTH, 0);
    glVertex2i(WIDTH, 0);
    glVertex2i(WIDTH, HEIGHT);
    glVertex2i(WIDTH - GUI_PANEL_WIDTH, HEIGHT);
    glEnd();

    // Draw title
    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(WIDTH - GUI_PANEL_WIDTH + 10, HEIGHT - 30, "Paint App");

    // Draw tools section
    drawText(WIDTH - GUI_PANEL_WIDTH + 10, HEIGHT - 60, "Tools:");
    for (int i = 0; i < sizeof(tools) / sizeof(tools[0]); i++) {
        // Draw button background
        if (i == currentTool) {
            glColor3f(0.7f, 0.7f, 0.9f); // Selected tool
        } else if (i == hoveredButton) {
            glColor3f(0.8f, 0.8f, 0.8f); // Hovered button
        } else {
            glColor3f(0.8f, 0.8f, 0.8f); // Normal button
        }
        
        glBegin(GL_QUADS);
        glVertex2i(WIDTH - GUI_PANEL_WIDTH + 10, HEIGHT - 90 - i * 30);
        glVertex2i(WIDTH - 10, HEIGHT - 90 - i * 30);
        glVertex2i(WIDTH - 10, HEIGHT - 110 - i * 30);
        glVertex2i(WIDTH - GUI_PANEL_WIDTH + 10, HEIGHT - 110 - i * 30);
        glEnd();

        // Draw tool icon
        glColor3fv(tools[i].color);
        glBegin(GL_QUADS);
        glVertex2i(WIDTH - GUI_PANEL_WIDTH + 15, HEIGHT - 95 - i * 30);
        glVertex2i(WIDTH - GUI_PANEL_WIDTH + 25, HEIGHT - 95 - i * 30);
        glVertex2i(WIDTH - GUI_PANEL_WIDTH + 25, HEIGHT - 105 - i * 30);
        glVertex2i(WIDTH - GUI_PANEL_WIDTH + 15, HEIGHT - 105 - i * 30);
        glEnd();

        // Draw tool text
        glColor3f(0.0f, 0.0f, 0.0f);
        drawText(WIDTH - GUI_PANEL_WIDTH + 35, HEIGHT - 100 - i * 30, tools[i].name + " (" + tools[i].shortcut + ")");
    }

    // Draw colors section
    int toolsCount = sizeof(tools) / sizeof(tools[0]);
    drawText(WIDTH - GUI_PANEL_WIDTH + 10, HEIGHT - 120 - toolsCount * 30, "Colors:");
    
    for (int i = 0; i < NUM_COLORS; i++) {
        // Draw color button
        if (i == selectedColor) {
            glColor3f(0.0f, 0.0f, 0.0f);
            glBegin(GL_LINE_LOOP);
            glVertex2i(WIDTH - GUI_PANEL_WIDTH + 10 + (i % 3) * 50, HEIGHT - 150 - toolsCount * 30 - (i / 3) * 50);
            glVertex2i(WIDTH - GUI_PANEL_WIDTH + 50 + (i % 3) * 50, HEIGHT - 150 - toolsCount * 30 - (i / 3) * 50);
            glVertex2i(WIDTH - GUI_PANEL_WIDTH + 50 + (i % 3) * 50, HEIGHT - 190 - toolsCount * 30 - (i / 3) * 50);
            glVertex2i(WIDTH - GUI_PANEL_WIDTH + 10 + (i % 3) * 50, HEIGHT - 190 - toolsCount * 30 - (i / 3) * 50);
            glEnd();
        }
        
        glColor3fv(colors[i]);
        glBegin(GL_QUADS);
        glVertex2i(WIDTH - GUI_PANEL_WIDTH + 15 + (i % 3) * 50, HEIGHT - 155 - toolsCount * 30 - (i / 3) * 50);
        glVertex2i(WIDTH - GUI_PANEL_WIDTH + 45 + (i % 3) * 50, HEIGHT - 155 - toolsCount * 30 - (i / 3) * 50);
        glVertex2i(WIDTH - GUI_PANEL_WIDTH + 45 + (i % 3) * 50, HEIGHT - 185 - toolsCount * 30 - (i / 3) * 50);
        glVertex2i(WIDTH - GUI_PANEL_WIDTH + 15 + (i % 3) * 50, HEIGHT - 185 - toolsCount * 30 - (i / 3) * 50);
        glEnd();
    }

    // Draw current color preview
    drawText(WIDTH - GUI_PANEL_WIDTH + 10, 50, "Current Color:");
    glColor3fv(currentColor);
    glBegin(GL_QUADS);
    glVertex2i(WIDTH - GUI_PANEL_WIDTH + 15, 15);
    glVertex2i(WIDTH - GUI_PANEL_WIDTH + 85, 15);
    glVertex2i(WIDTH - GUI_PANEL_WIDTH + 85, 45);
    glVertex2i(WIDTH - GUI_PANEL_WIDTH + 15, 45);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(WIDTH - GUI_PANEL_WIDTH + 15, 15);
    glVertex2i(WIDTH - GUI_PANEL_WIDTH + 85, 15);
    glVertex2i(WIDTH - GUI_PANEL_WIDTH + 85, 45);
    glVertex2i(WIDTH - GUI_PANEL_WIDTH + 15, 45);
    glEnd();
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw the canvas
    glBegin(GL_POINTS);
    for (int x = 0; x < WIDTH - GUI_PANEL_WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            glColor3f(canvas[x][y * 3], canvas[x][y * 3 + 1], canvas[x][y * 3 + 2]);
            glVertex2i(x, y);
        }
    }
    glEnd();
    
    // Draw preview for line, rectangle, circle
    if (isDrawing && (currentTool == LINE || currentTool == RECTANGLE || currentTool == CIRCLE)) {
        glColor3fv(currentColor);
        glBegin(GL_LINES);
        
        if (currentTool == LINE) {
            glVertex2i(startX, startY);
            glVertex2i(prevX, prevY);
        } else if (currentTool == RECTANGLE) {
            glVertex2i(startX, startY); glVertex2i(prevX, startY);
            glVertex2i(prevX, startY); glVertex2i(prevX, prevY);
            glVertex2i(prevX, prevY); glVertex2i(startX, prevY);
            glVertex2i(startX, prevY); glVertex2i(startX, startY);
        } else if (currentTool == CIRCLE) {
            int radius = static_cast<int>(sqrt(pow(prevX - startX, 2) + pow(prevY - startY, 2)));
            for (int i = 0; i < 360; i++) {
                float angle = i * 3.14159f / 180;
                int x = startX + radius * cos(angle);
                int y = startY + radius * sin(angle);
                glVertex2i(startX, startY);
                glVertex2i(x, y);
            }
        }
        
        glEnd();
    }
    
    // Draw the GUI
    drawGUI();
    
    glutSwapBuffers();
}

// Check if a point is in a button
bool isInButton(int x, int y, int buttonX, int buttonY, int width, int height) {
    return x >= buttonX && x <= buttonX + width && y >= buttonY && y <= buttonY + height;
}

// Mouse callback function
void mouse(int button, int state, int x, int y) {
    y = HEIGHT - y; // Flip y coordinate to match OpenGL coordinates
    
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            // Check if click is in GUI panel
            if (x >= WIDTH - GUI_PANEL_WIDTH) {
                // Check tool buttons
                int toolsCount = sizeof(tools) / sizeof(tools[0]);
                for (int i = 0; i < toolsCount; i++) {
                    if (isInButton(x, y, WIDTH - GUI_PANEL_WIDTH + 10, HEIGHT - 110 - i * 30, GUI_PANEL_WIDTH - 20, 20)) {
                        currentTool = static_cast<Tool>(i);
                        glutPostRedisplay();
                        return;
                    }
                }
                
                // Check color buttons
                for (int i = 0; i < NUM_COLORS; i++) {
                    if (isInButton(x, y, 
                        WIDTH - GUI_PANEL_WIDTH + 10 + (i % 3) * 50, 
                        HEIGHT - 190 - toolsCount * 30 - (i / 3) * 50, 
                        40, 40)) {
                        currentColor[0] = colors[i][0];
                        currentColor[1] = colors[i][1];
                        currentColor[2] = colors[i][2];
                        selectedColor = i;
                        glutPostRedisplay();
                        return;
                    }
                }
                
                return; // Don't draw if clicking in GUI panel
            }
            
            // Handle drawing tools
            isDrawing = true;
            startX = x;
            startY = y;
            prevX = x;
            prevY = y;
            
            if (currentTool == COLOR_PICKER) {
                // Read pixel color at (x, y)
                if (x >= 0 && x < WIDTH - GUI_PANEL_WIDTH && y >= 0 && y < HEIGHT) {
                    currentColor[0] = canvas[x][y * 3];
                    currentColor[1] = canvas[x][y * 3 + 1];
                    currentColor[2] = canvas[x][y * 3 + 2];
                    
                    // Find which predefined color this matches (if any)
                    selectedColor = -1;
                    for (int i = 0; i < NUM_COLORS; i++) {
                        if (colors[i][0] == currentColor[0] && 
                            colors[i][1] == currentColor[1] && 
                            colors[i][2] == currentColor[2]) {
                            selectedColor = i;
                            break;
                        }
                    }
                    
                    printf("Selected color: R=%.2f, G=%.2f, B=%.2f\n", currentColor[0], currentColor[1], currentColor[2]);
                }
            } else if (currentTool == FILL) {
                saveState();
                
                float oldColor[3] = {
                    canvas[x][y * 3],
                    canvas[x][y * 3 + 1],
                    canvas[x][y * 3 + 2]
                };
                
                if (oldColor[0] != currentColor[0] || oldColor[1] != currentColor[1] || oldColor[2] != currentColor[2]) {
                    floodFill(x, y, oldColor, currentColor);
                }
                
                glutPostRedisplay();
            } else if (currentTool == PENCIL || currentTool == ERASER) {
                saveState();
                drawPoint(x, y);
                glutPostRedisplay();
            }
        } else if (state == GLUT_UP && isDrawing) {
            isDrawing = false;
            
            if (currentTool == LINE) {
                saveState();
                drawLine(startX, startY, x, y);
                glutPostRedisplay();
            } else if (currentTool == RECTANGLE) {
                saveState();
                drawRectangle(startX, startY, x, y);
                glutPostRedisplay();
            } else if (currentTool == CIRCLE) {
                saveState();
                int radius = static_cast<int>(sqrt(pow(x - startX, 2) + pow(y - startY, 2)));
                drawCircle(startX, startY, radius);
                glutPostRedisplay();
            }
        }
    }
}

// Mouse motion callback function
void motion(int x, int y) {
    y = HEIGHT - y; // Flip y coordinate
    
    // Check for button hover in GUI panel
    hoveredButton = -1;
    if (x >= WIDTH - GUI_PANEL_WIDTH) {
        int toolsCount = sizeof(tools) / sizeof(tools[0]);
        for (int i = 0; i < toolsCount; i++) {
            if (isInButton(x, y, WIDTH - GUI_PANEL_WIDTH + 10, HEIGHT - 110 - i * 30, GUI_PANEL_WIDTH - 20, 20)) {
                hoveredButton = i;
                break;
            }
        }
        glutPostRedisplay();
        return; // Don't draw if moving in GUI panel
    }
    
    if (isDrawing) {
        if (currentTool == PENCIL || currentTool == ERASER) {
            drawLine(prevX, prevY, x, y);
            glutPostRedisplay();
        }
        prevX = x;
        prevY = y;
    }
}

// Passive mouse motion callback (for hover effects)
void passiveMotion(int x, int y) {
    y = HEIGHT - y; // Flip y coordinate
    
    // Check for button hover in GUI panel
    hoveredButton = -1;
    if (x >= WIDTH - GUI_PANEL_WIDTH) {
        int toolsCount = sizeof(tools) / sizeof(tools[0]);
        for (int i = 0; i < toolsCount; i++) {
            if (isInButton(x, y, WIDTH - GUI_PANEL_WIDTH + 10, HEIGHT - 110 - i * 30, GUI_PANEL_WIDTH - 20, 20)) {
                hoveredButton = i;
                break;
            }
        }
        glutPostRedisplay();
    }
}

// Keyboard callback function
void keyboard(unsigned char key, int x, int y) {
    switch (tolower(key)) {
        case 'p': currentTool = PENCIL; printf("Pencil tool selected\n"); break;
        case 'l': currentTool = LINE; printf("Line tool selected\n"); break;
        case 'r': currentTool = RECTANGLE; printf("Rectangle tool selected\n"); break;
        case 'c': currentTool = CIRCLE; printf("Circle tool selected\n"); break;
        case 'e': currentTool = ERASER; printf("Eraser tool selected\n"); break;
        case 'f': currentTool = FILL; printf("Fill tool selected\n"); break;
        case 'k': currentTool = COLOR_PICKER; printf("Color picker tool selected\n"); break;
        case 'z': if (glutGetModifiers() == GLUT_ACTIVE_CTRL) undo(); break;
        case 'y': if (glutGetModifiers() == GLUT_ACTIVE_CTRL) redo(); break;
        case 'g': showGUI = !showGUI; break; // Toggle GUI visibility
        case 'q': exit(0); break;
    }
    glutPostRedisplay();
}

// Initialize OpenGL
void init() {
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    
    // Set point size for better visibility
    glPointSize(3.0f);
    
    initCanvas();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("2D Paint App with GUI");
    
    init();
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passiveMotion);
    glutKeyboardFunc(keyboard);
    
    printf("2D Paint App with GUI\n");
    printf("Tools:\n");
    printf("  p - Pencil\n");
    printf("  l - Line\n");
    printf("  r - Rectangle\n");
    printf("  c - Circle\n");
    printf("  e - Eraser\n");
    printf("  f - Fill\n");
    printf("  k - Color Picker\n");
    printf("  Ctrl+z - Undo\n");
    printf("  Ctrl+y - Redo\n");
    printf("  g - Toggle GUI\n");
    printf("  q - Quit\n");
    
    glutMainLoop();
    return 0;
}