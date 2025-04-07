#include <stdio.h>
#include <GL/glut.h>

int n; 
int cellWidth, cellHeight;


void bresLine(int xa, int ya, int xb, int yb) {
    int dx = abs(xb - xa), dy = abs(yb - ya);
    int sx = (xa < xb) ? 1 : -1;
    int sy = (ya < yb) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        glVertex2i(xa, ya); 
        if (xa == xb && ya == yb) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            xa += sx;
        }
        if (e2 < dx) {
            err += dx;
            ya += sy;
        }
    }
}


void drawGridBoundaries() {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);

    
    for (int i = 0; i <= n; i++) {
        int x = i * cellWidth;
        bresLine(x, 0, x, 480);
    }

  
    for (int i = 0; i <= n; i++) {
        int y = i * cellHeight;
        bresLine(0, y, 640, y);
    }

    glEnd();
}


void drawChessboard() {
    cellWidth = 640 / n;
    cellHeight = 640 / n;

    glBegin(GL_QUADS);
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) { 
            if ((i + j) % 2 == 0)
                glColor3f(1.0, 1.0, 1.0);
            else
                glColor3ub(204, 142, 35); 

            
            int x1 = j * cellWidth;
            int y_1 = i * cellHeight;
            int x2 = (j + 1) * cellWidth;
            int y2 = (i + 1) * cellHeight;

            glVertex2i(x1, y_1);
            glVertex2i(x2, y_1);
            glVertex2i(x2, y2);
            glVertex2i(x1, y2);
        }
    }
    glEnd();
}


void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    
    drawChessboard();
    drawGridBoundaries();

    glFlush();
}


int main(int argc, char **argv) {
    printf("Enter the number of Rows / Columns: ");
    scanf("%d", &n);

    if (n <= 0 || n > 150) {
        printf("Invalid value! Using default n = 8.\n");
        n = 8; 
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 640);
    glutCreateWindow("Assign-3 : Bresnum Line ");

    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 640, 0, 640);       

    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}
