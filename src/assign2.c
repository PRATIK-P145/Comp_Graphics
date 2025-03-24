#include <stdio.h>
#include <GL/glut.h>

int count = 0;
int clickCount = 0;
int style = 1;

int mapX1 = 0, mapy_1 = 0, mapX2 = 0, mapY2 = 0;

int abs(int value) {
    if (value < 0)
        return (-1 * value);
    return value;
}

int Round(float value) {
    if (value < 0) {
        return (int)(value - 0.5);
    }
    return (int)(value + 0.5);
}

void drawPoint(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2d(x + 320, y + 240);
    glEnd();
}

void drawDashedLine(float x, float y) {
    if (count < 7) {
        count++;
        drawPoint(Round(x), Round(y));
    } else if (count >= 7 && count <= 12) {
        count++;
    } else {
        count = 0;
    }
}

void drawDottedDashLine(float x, float y) {
    if (count < 7) {
        drawPoint(Round(x), Round(y));
        count++;
    } else if (count >= 7 && count <= 15) {
        if (count == 11) {
            drawPoint(Round(x), Round(y));
        }
        count++;
    } else {
        count = 0;
    }
}

void BresLine(int xa, int ya, int xb, int yb) {
    int dx, dy, steps;

    dx = xb - xa;
    dy = yb - ya;

    if (abs(dy) > abs(dx)) {
        steps = abs(dy);
    } else {
        steps = abs(dx);
    }

    float xinc = (float)dx / steps;
    float yinc = (float)dy / steps;

    drawPoint(xa, ya);

    float x = xa;
    float y = ya;

    for (int i = 0; i <= steps; i++) {
        x += xinc;
        y += yinc;

        switch (style) {
        case 1: 
            drawPoint(Round(x), Round(y));
            break;
        case 2: 
            if (i % 4 == 0) {
                drawPoint(Round(x), Round(y));
            }
            break;
        case 3: 
            drawDashedLine(x, y);
            break;
        case 4: 
            drawDottedDashLine(x, y);
            break;
        default:
            drawPoint(Round(x), Round(y)); 
            break;
        }
    }
}


void MouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        clickCount++;
        if(clickCount>2)
            clickCount=1;

        if (clickCount == 1) {
            mapX1 = x - 320; 
            mapy_1 = 240 - y; 
           // printf("\nFirst Click at (%d, %d)", mapX1, mapy_1);
        } else if (clickCount == 2) {
            mapX2 = x - 320; 
            mapY2 = 240 - y; 
            //printf("\nSecond Click at (%d, %d)", mapX2, mapY2);

        }
    }
}


void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);

    BresLine(0, -240, 0, 240);  
    BresLine(-320, 0, 320, 0);  

    glColor3f(0, 0, 0);

    
    if (clickCount==1) {
        drawPoint(mapX1, mapy_1);
    }else if(clickCount==2){
        BresLine(mapX1, mapy_1, mapX2, mapY2);
    }
    glFlush();
}


void main(int argc, char **argv) {
    printf("\n==== Styles ====");
    printf("\n 1. Simple Line");
    printf("\n 2. Dotted Line");
    printf("\n 3. Dashed Line");
    printf("\n 4. Dotted-Dashed Line");
    printf("\nEnter your Choice: ");
    scanf("%d", &style);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("DDA Line Drawing with Styles");

    glClearColor(1, 1, 1, 0);
    glColor3f(0, 0, 0);

    gluOrtho2D(0, 640, 0, 480);

    glutDisplayFunc(draw);
    glutMouseFunc(MouseClick);

    glutMainLoop();
}
