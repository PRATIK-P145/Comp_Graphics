#include<GL/glut.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>

float border[3] = {0.0,0.0,0.0};
float  blue[3] = {0.0,0.0,1.0};
float  red[3] = {1.0,0.0,0.0};

void newXY(int x, int y){
    int newX = x + 320;
    int newY = y + 240;
    printf("%d, %d\n",newX,newY);
    glVertex2d(newX, newY);
}

void BoundryFill(int x, int y, float bColor[3], float fillColor[3]){
	float current[3];
	
	glReadPixels(x, y, 1.0,1.0,  GL_RGB, GL_FLOAT, current);
	
	if( (current[0]!= bColor[0] || current[1]!= bColor[1] || current[2]!= bColor[2] ) &&
             (current[0]!= fillColor[0] || current[1]!= fillColor[1]  || current[2]!= fillColor[2])  )
        {  
        	glColor3f(fillColor[0],fillColor[1], fillColor[2]);
        	glBegin(GL_POINTS);
        		glVertex2d(x,y);
        	glEnd();
        	glFlush();
        	
        	 BoundryFill(x+1, y ,bColor, fillColor);
        	 BoundryFill(x-1, y, bColor, fillColor);
        	 BoundryFill(x, y+1 ,bColor, fillColor);
        	  BoundryFill(x, y-1, bColor, fillColor);
	}
	

}

float rad(float deg){
    return ((M_PI*deg)/180);
}

void draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    //glBegin(GL_POINTS);

    int r = 200;
    glBegin(GL_LINE_LOOP);

    // glVertex2d(0,r);
    // glVertex2d(-r*cos(rad(18)),r*sin(rad(18)));
    // glVertex2d(-r*cos(rad(54)),-r*sin(rad(54))); // should be in third Quadrant
    // glVertex2d(r*cos(rad(54)),-r*sin(rad(54)));
    // glVertex2d(r*cos(rad(18)),r*sin(rad(18)));
    int y = 1;
    glColor3f(0,0,0); 
    newXY(0,y*r);
    newXY(-r*cos(rad(54)),-r*y*sin(rad(54)));
    newXY(r*cos(rad(18)),r*y*sin(rad(18)));
    newXY(-r*cos(rad(18)),r*y*sin(rad(18)));
    newXY(r*cos(rad(54)),-r*y*sin(rad(54)));

    glEnd();
    glFlush();

    
    BoundryFill(0+320,r-5+240,border,blue);
    BoundryFill(203+5,79+5,border,blue);
    BoundryFill(510-5,301-2,border,blue);
    BoundryFill(130+5,301-2,border,blue);
    BoundryFill(437-5,79+5,border,blue);
    BoundryFill(320,240,border,red);
}


int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowSize(640,480);// 640, 480
    glutInitWindowPosition(0,0);
    glutCreateWindow("Window");

    glClearColor(1,1,1,0);
    glColor3f(1,0,0);

    //gluOrtho2D(0,640,0,480);
    gluOrtho2D(0,640,0,480);

    glutDisplayFunc(draw);
    glutMainLoop();

return 0;

}
