#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#define M_PI 3.14159265358979323846
int v;
float xf, yf, radian;
float input[3][15], output[3][15], t[3][3], s[3][3], r[3][3], Rx[3][3], Ry[3][3], Rxy[3][3], shx[3][3], shy[3][3];

void mul(float input[3][15], float m[3][3], float output[3][15], int v) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < v; j++) {
            output[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                output[i][j] += m[i][k] * input[k][j];
            }
        }
    }
}

void translation() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                t[i][j] = 1;
            } else {
                t[i][j] = 0;
            }
        }
    }
    printf("Enter the translation distance (tx,ty): ");
    scanf("%f%f", &xf, &yf);
    t[0][2] = xf;
    t[1][2] = yf;
    mul(input, t, output, v);
}

void Rotation() {
    float o;
    int xr, yr;
    printf("Enter the fixed point (xr,yr): ");
    scanf("%d%d", &xr, &yr);
    printf("Enter the angle in degrees: ");
    scanf("%f", &o);
    radian = o * M_PI / 180;
    r[0][0] = cos(o);
    r[0][1] = -sin(o);
    r[0][2] = xr * (1 - cos(o)) + yr * sin(o);
    r[1][0] = sin(o);
    r[1][1] = cos(o);
    r[1][2] = yr * (1 - cos(o)) - xr * sin(o);
    r[2][0] = 0;
    r[2][1] = 0;
    r[2][2] = 1;
    mul(input, r, output, v);
}

void Scaling() {
    int sx, sy;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                s[i][j] = 1;
            } else {
                s[i][j] = 0;
            }
        }
    }
    printf("Enter the scaling (sx,sy): ");
    scanf("%d%d", &sx, &sy);
    s[0][0] = sx;
    s[1][1] = sy;
    printf("Enter the fixed point (xf,yf): ");
    scanf("%f%f", &xf, &yf);
    s[0][2] = xf * (1 - sx);
    s[1][2] = yf * (1 - sx);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f\t", s[i][j]);
        }
        printf("\n");
    }
    mul(input, s, output, v);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < v; j++) {
            printf("%f\t", output[i][j]);
        }
        printf("\n");
    }
}

void Reflection_x() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                Rx[i][j] = 1;
            } else {
                Rx[i][j] = 0;
            }
        }
    }
    Rx[1][1] = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f\t", Rx[i][j]);
        }
        printf("\n");
    }
    mul(input, Rx, output, v);
}

void Reflection_y() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                Ry[i][j] = 1;
            } else {
                Ry[i][j] = 0;
            }
        }
    }
    Ry[0][0] = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f\t", Ry[i][j]);
        }
        printf("\n");
    }
    mul(input, Ry, output, v);
}

void Reflection_o() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Rxy[i][j] = 0;
        }
    }
    Rxy[0][0] = -1;
    Rxy[1][1] = -1;
    Rxy[2][2] = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f\t", Rxy[i][j]);
        }
        printf("\n");
    }
    mul(input, Rxy, output, v);
}

void Reflection_xy() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Rxy[i][j] = 0;
        }
    }
    Rxy[0][1] = 1;
    Rxy[1][0] = 1;
    Rxy[2][2] = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f\t", Rxy[i][j]);
        }
        printf("\n");
    }
    mul(input, Rxy, output, v);
}

void Reflection_xy1() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Rxy[i][j] = 0;
        }
    }
    Rxy[0][1] = -1;
    Rxy[1][0] = -1;
    Rxy[2][2] = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f\t", Rxy[i][j]);
        }
        printf("\n");
    }
    mul(input, Rxy, output, v);
}

void Shearx() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                shx[i][j] = 1;
            } else {
                shx[i][j] = 0;
            }
        }
    }
    printf("Enter the shrx: ");
    scanf("%f", &xf);
    printf("Enter the fixed yref: ");
    scanf("%f", &yf);
    shx[0][1] = xf;
    shx[0][2] = -(xf * yf);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f\t", shx[i][j]);
        }
        printf("\n");
    }
    mul(input, shx, output, v);
}

void sheary() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                shy[i][j] = 1;
            } else {
                shy[i][j] = 0;
            }
        }
    }
    printf("Enter the shry: ");
    scanf("%f", &xf);
    printf("Enter the Xref: ");
    scanf("%f", &yf);
    shy[1][0] = xf;
    shy[1][2] = -(xf * yf);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f\t", shy[i][j]);
        }
        printf("\n");
    }
    mul(input, shy, output, v);
}

int Round(float a) {
    return (int)(a + 0.5);
}

void DDAl(int xa, int ya, int xb, int yb) {
    int dx, dy, steps;
    dx = xb - xa;
    dy = yb - ya;
    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
    } else {
        steps = abs(dy);
    }
    float xinc, yinc, x, y;
    xinc = (float)dx / steps;
    yinc = (float)dy / steps;
    x = xa;
    y = ya;
    glVertex2d(xa, ya);
    for (int i = 0; i <= steps; i++) {
        x = x + xinc;
        y = y + yinc;
        glVertex2d(Round(320 + x), Round(240 + y));
    }
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    DDAl(0, -240, 0, 240);
    DDAl(-320, 0, 320, 0);
    int i;
    for (i = 0; i < v - 1; i++) {
        DDAl(input[0][i], input[1][i], input[0][i + 1], input[1][i + 1]);
    }
    DDAl(input[0][i], input[1][i], input[0][0], input[1][0]);
    glEnd();
    glFlush();
    //usleep(500000);

    int ch;
    do {
        printf("1.Translation\n2.Rotation\n3.Scaling\n4.Reflection\n5.Shearing\nEnter your Choice:\n");
        scanf("%d", &ch);
        int ref;
        int sh;
        switch (ch) {
            case 1:
                translation();
                break;
            case 2:
                Rotation();
                break;
            case 3:
                Scaling();
                break;
            
        }
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POINTS);
        DDAl(0, -240, 0, 240);
        DDAl(-320, 0, 320, 0);
        for (i = 0; i < v - 1; i++) {
            DDAl(output[0][i], output[1][i], output[0][i + 1], output[1][i + 1]);
        }
        DDAl(output[0][v - 1], output[1][v - 1], output[0][0], output[1][0]);
        glEnd();
        glFlush();
        //usleep(5000000);
    } while (ch < 6);
}

int main(int argc, char **argv) {
    float x, y;
    printf("Enter the no of vertices: ");
    scanf("%d", &v);
    for (int i = 0; i < v; i++) {
        printf("Enter coordinates (x,y): ");
        scanf("%f%f", &x, &y);
        input[0][i] = x;
        input[1][i] = y;
        input[2][i] = 1;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < v; j++) {
            printf("%f\t", input[i][j]);
        }
        printf("\n");
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(900, 0);
    glutCreateWindow("Assign 9");
    glClearColor(1.0, 1.0, 1.0, 0);
    glColor3f(0, 0, 0);
    gluOrtho2D(0, 640, 0, 480);
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}