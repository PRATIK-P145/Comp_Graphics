#include <GL/glut.h>
#include <math.h>
#include <windows.h>   // For PlaySound
#include <mmsystem.h>  // Link with winmm.lib

#pragma comment(lib, "winmm.lib") // Linker directive for sound

float ballX = 0.0f;
float ballY = 0.0f;
float velocityY = 0.02f;
float gravity = -0.001f;
float radius = 0.1f;
float moveSpeed = 0.05f;
bool soundEnabled = false;

// Draw a filled circle
void drawBall(float x, float y) {
    int num_segments = 100;
    float angle;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.0, 0.0);  // Red ball
    glVertex2f(x, y);  // Center

    for (int i = 0; i <= num_segments; ++i) {
        angle = 2.0f * 3.14159f * i / num_segments;
        glVertex2f(
            x + cos(angle) * radius,
            y + sin(angle) * radius
        );
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBall(ballX, ballY);
    glutSwapBuffers();
}

// Sound on bounce
void playBounceSound() {
    if (soundEnabled) {
        PlaySound(TEXT("bounce.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
}

// Update physics
void update(int value) {
    velocityY += gravity;
    ballY += velocityY;

    // Bounce logic
    if (ballY - radius < -1.0f) {
        ballY = -1.0f + radius;
        velocityY = -velocityY * 0.9f;

        playBounceSound();  // Play sound
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Keyboard controls
void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        if (ballX - radius > -1.0f)
            ballX -= moveSpeed;
        break;
    case GLUT_KEY_RIGHT:
        if (ballX + radius < 1.0f)
            ballX += moveSpeed;
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case ' ': // Spacebar to jump
        velocityY = 0.03f;
        break;
    case 's': // Toggle sound
    case 'S':
        soundEnabled = !soundEnabled;
        break;
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bouncing Ball with Controls and Sound");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutSpecialFunc(specialKeys); // Arrow keys
    glutKeyboardFunc(keyboard);   // Spacebar and toggle sound

    glutMainLoop();
    return 0;
}
