#include <GL/glut.h>
#include <vector>
using namespace std;

int xa, ya,  xb,  yb;
int count =0;
struct Line{
    int x1,y1;
    int x2,y2;
};

vector<Line>Lines;


void MouseClick(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        count++;
        if(count == 1){
            xa = x;
            ya = y;
        
        }else if(count == 2){
            xb = x;
            yb = y;
            Lines.push_back({xa,(480-ya),xb,(480-yb)});
           count =0;
        }
            
    }
}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    for(Line temp: Lines){   
        glVertex2d(temp.x1,temp.y1);
        glVertex2d(temp.x2,temp.y2);   
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