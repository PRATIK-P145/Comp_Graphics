#include<stdio.h>
#include<GL/glut.h>

int pos = 15;  // Initial position
int desc = 1;   // Direction of movement

void display(){
   // printf("Display called\n");  // Check if display is called
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
        glVertex2d(pos + 150, 150);
        glVertex2d(pos - 150, 150);
        glVertex2d(pos - 150, -150);
        glVertex2d(pos + 150, -150);
    glEnd();

    glutSwapBuffers();  // Correct for double buffering
}

void update(){
   // printf("Update called\n");  // Check if update is called

    pos = pos + 0.9 * desc;

    // Reverse direction if boundary is hit
    if(pos >= 220 || pos <= -220){
        desc *= -1;
    }

    glutPostRedisplay();  // Request redisplay
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Correct double buffering

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);

    glutCreateWindow("Real-Time Changes in Window");

    // Set viewport and projection
    glViewport(0, 0, 640, 480);
    gluOrtho2D(-320.0, 320.0, -240.0, 240.0);

    glClearColor(0, 0, 0, 0);  // Black background
    glColor3f(0, 1, 0);        // Green square

    // Bind callbacks
    glutDisplayFunc(display);
    glutIdleFunc(update);

    glutMainLoop();

    return 0;
}
