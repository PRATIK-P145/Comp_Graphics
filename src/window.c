#include <GL/glut.h>
//gcc app.c -I"d:\Programs\Comp_Graphics\include" -L"d:\Programs\Comp_Graphics\lib" -lfreeglut -lopengl32 -lgdi32 -lglu32 -o app.exe

void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
    glFlush();                     // Render the content immediately
}

int main(int argc, char** argv) {

    glutInit (&argc , argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);

    glutCreateWindow("Window");

    glClearColor(0.0, 0.0, 0.0, 0);  // Background Color
    glColor3f(0.0,1.0,0.0);    // Pen color

    gluOrtho2D(0,640,0,480);

    glutDisplayFunc(display);
    glutMainLoop();


    return 0;
}
