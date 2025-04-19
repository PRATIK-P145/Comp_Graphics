#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

float ctrlPoints[4][2];
int pointCount = 0;

void drawBezier()
{
    glBegin(GL_LINE_STRIP);
    for(float u=0;u<=1;u+=0.1){
        float x=0,y=0;

        if (pointCount==2){
            x=(1-u)*ctrlPoints[0][0] + u*ctrlPoints[1][0];
            y=(1-u)*ctrlPoints[0][1] + u*ctrlPoints[1][1];
        }
        else if(pointCount==3){
            x=pow(1-u,2)*ctrlPoints[0][0] + 2*u*(1-u)+ctrlPoints[1][0] + pow(u,2)*ctrlPoints[2][0];
            y=pow(1-u,2)*ctrlPoints[0][1] + 2*u*(1-u)+ctrlPoints[1][1] + pow(u,2)*ctrlPoints[2][1];
        }
        else if(pointCount==4){
            x=pow(1-u,3)*ctrlPoints[0][0] + 3*u*pow(1-u,2)*ctrlPoints[1][0] + 3*pow(u,2)*(1-u)*ctrlPoints[2][0]+pow(u,3)*ctrlPoints[3][0];
            y=pow(1-u,3)*ctrlPoints[0][1] + 3*u*pow(1-u,2)*ctrlPoints[1][1] + 3*pow(u,2)*(1-u)*ctrlPoints[2][1]+pow(u,3)*ctrlPoints[3][1];
        }
        glVertex2f(x,y);
    } 
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    //we're Plotting the points to represent p0, p1,....etc
    glPointSize(5);
    glBegin(GL_POINTS);
    for(int i=0; i<pointCount; i++){
        glVertex2f(ctrlPoints[i][0],ctrlPoints[i][1]);
    }
    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_LINE_STRIP);
    for(int i=0; i<pointCount; i++){
        glVertex2f(ctrlPoints[i][0],ctrlPoints[i][1]);
    }
    glEnd();

    if(pointCount>=2){
        drawBezier();
    }
    glFlush();

}

void mouse(int button, int state , int x, int y ){
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        if(pointCount<4){
            ctrlPoints[pointCount][0] = x;
            ctrlPoints[pointCount][1] = 480-y;
            pointCount++;
        }
        else{
            pointCount++;
        }
        glutPostRedisplay();
    }
}


int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("Bezier curve");

	glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
	glColor3f(0,1,0);

	gluOrtho2D(0,640,0,480);

	glutDisplayFunc(display);
    glutMouseFunc(mouse);
	glutMainLoop();

	return 0;

}