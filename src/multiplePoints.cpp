#include <GL/glut.h>
#include <vector>
using namespace std;

int xa, ya,  xb,  yb;
int count =0;
struct pt{
    int x1,y1;
};

vector<pt>Points;


void MouseClick(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        count++;
        if(count == 1){
            xa = x;
            ya = y;
            Points.push_back({xa,(480-ya)});
           count =0;
        }
            
    }
}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for(pt temp: Points){   
        glVertex2d(temp.x1,temp.y1);   
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutCreateWindow("MOuse Line");

    glClearColor(0,0,0,0);
    glColor3f(0,1,0);
    gluOrtho2D(0,640,0,480);

    glutDisplayFunc(Display);
    glutMouseFunc(MouseClick);

    glutMainLoop();


  return 0;
}