#include <GL/glut.h>
#include <algorithm>
#include <vector>
#include <windows.h>  // For Sleep() on Windows


using namespace std;

// Define a structure for vertices
struct Vertex {
    float x, y;
};

// Define the polygon vertices
vector<Vertex> polygon = {
    {150.0f, 150.0f},
    {200.0f, 150.0f},
    {250.0f, 200.0f},
    {150.0f, 300.0f},
    {50.0f, 200.0f}
};

// Delay function for cross-platform support
void delay(int milliseconds) {
    Sleep(milliseconds);  // Sleep in milliseconds (Windows)
}

// Draw a point at (x, y)
void drawPoint(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();  // Ensure the point is displayed
}

// Scanline fill algorithm with delay
void scanlineFill(vector<Vertex>& vertices) {
    int n = vertices.size();
    
    // Find min and max Y coordinates
    float minY = vertices[0].y, maxY = vertices[0].y;
    for (int i = 1; i < n; ++i) {
        if (vertices[i].y < minY) minY = vertices[i].y;
        if (vertices[i].y > maxY) maxY = vertices[i].y;
    }

    // Loop through each scanline from minY to maxY
    for (int y = (int)minY; y <= (int)maxY; ++y) {
        vector<float> intersections;

        // Find intersections with edges
        for (int i = 0; i < n; ++i) {
            Vertex v1 = vertices[i];
            Vertex v2 = vertices[(i + 1) % n];  // Connect to next vertex

            // Check if scanline intersects the edge
            if ((v1.y <= y && v2.y > y) || (v2.y <= y && v1.y > y)) {
                float x = v1.x + (y - v1.y) * (v2.x - v1.x) / (v2.y - v1.y);
                intersections.push_back(x);
            }
        }

        // Sort intersections by X-coordinate
        sort(intersections.begin(), intersections.end());

        // Fill pixels between pairs of intersections
        for (size_t i = 0; i < intersections.size(); i += 2) {
            if (i + 1 < intersections.size()) {
                int xStart = (int)intersections[i];
                int xEnd = (int)intersections[i + 1];
                for (int x = xStart; x <= xEnd; ++x) {
                    drawPoint(x, y);
                    delay(0.1);  // Delay to visualize filling (1 ms delay)
                }
            }
        }
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the polygon color to red
    glColor3f(1.0f, 0.0f, 0.0f);

    // Fill the polygon using the scanline algorithm with delay
    scanlineFill(polygon);

    // Draw the outline of the polygon
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    for (const auto& v : polygon) {
        glVertex2f(v.x, v.y);
    }
    glEnd();

    glFlush();
}

// Initialization function
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Set background to white
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);  // Set the coordinate system
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Custom Polygon Fill Using Scanline Algorithm with Delay");

    init();  // Initialize the window
    glutDisplayFunc(display);  // Register display callback
    glutMainLoop();  // Enter the main loop

    return 0;
}
