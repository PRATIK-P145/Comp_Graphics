#include <GL/freeglut.h>
#include <vector>
#include <cstdlib>
#include <cmath>

struct Particle {
    float x, y;
    float vx, vy;
    float r, g, b;
    float lifetime;
};

struct Firework {
    float x, y;
    float vy;
    float r, g, b;
    bool isRising;
    std::vector<Particle> particles;
};

std::vector<Firework> fireworks;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float GRAVITY = 0.1f;

void init() {
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glPointSize(4.0f);
}

void createParticles(Firework& fw) {
    for (int i = 0; i < 100; ++i) {
        Particle p;
        p.x = fw.x;
        p.y = fw.y;
        float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.0f;
        float speed = static_cast<float>(rand() % 5 + 2);
        p.vx = cos(angle) * speed;
        p.vy = sin(angle) * speed;
        p.r = fw.r + static_cast<float>(rand() % 100 - 50)/255.0f;
        p.g = fw.g + static_cast<float>(rand() % 100 - 50)/255.0f;
        p.b = fw.b + static_cast<float>(rand() % 100 - 50)/255.0f;
        p.lifetime = 1.0f;
        fw.particles.push_back(p);
    }
}

void updateFireworks() {
    for (auto it = fireworks.begin(); it != fireworks.end();) {
        if (it->isRising) {
            it->y += it->vy;
            if (it->y >= WINDOW_HEIGHT - 50) {
                it->isRising = false;
                createParticles(*it);
            }
            ++it;
        } else {
            bool allDead = true;
            for (auto& p : it->particles) {
                p.vy -= GRAVITY;
                p.x += p.vx;
                p.y += p.vy;
                p.lifetime -= 0.01f;
                if (p.lifetime > 0 && p.y > 0) allDead = false;
            }
            if (allDead) {
                it = fireworks.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void drawFireworks() {
    glBegin(GL_POINTS);
    for (const auto& fw : fireworks) {
        if (fw.isRising) {
            glColor3f(fw.r, fw.g, fw.b);
            glVertex2f(fw.x, fw.y);
        } else {
            for (const auto& p : fw.particles) {
                if (p.lifetime > 0 && p.y > 0) {
                    glColor3f(p.r, p.g, p.b);
                    glVertex2f(p.x, p.y);
                }
            }
        }
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawFireworks();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        Firework newFw;
        newFw.x = x;
        newFw.y = WINDOW_HEIGHT - y;
        newFw.vy = 8.0f;
        newFw.r = static_cast<float>(rand()) / RAND_MAX;
        newFw.g = static_cast<float>(rand()) / RAND_MAX;
        newFw.b = static_cast<float>(rand()) / RAND_MAX;
        newFw.isRising = true;
        fireworks.push_back(newFw);
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
}

void update(int value) {
    updateFireworks();
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Firework Animation");
    init();
    glutDisplayFunc(display
    
    );
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}