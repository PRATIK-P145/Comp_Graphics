#include <stdio.h>
#include<GL/glut.h>

//int xmin, ymin, xmax, ymax;
int x, y,n;
float bColor[3] = {0.0,0.0,0.0};
float  fillColor[3] = {1.0,0.0,0.0};
int arr[2][20];

void DDALine(int x1, int y1, int x2, int y2){
        glBegin(GL_LINES);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glEnd();
}

void drawPolygon(int arr[2][20], int n){
	
	for(int i=0; i<n; i++){
		DDALine(arr[0][i], arr[1][i], arr[0][i+1], arr[1][i+1]); 
	}
}

void BoundryFill(int x, int y, float bColor[3], float fillColor[3]){
	float current[3];
	
	glReadPixels(x, y, 1.0,1.0,  GL_RGB, GL_FLOAT, current);
	
	if( (current[0]!= bColor[0] || current[1]!= bColor[1] || current[2]!= bColor[2] ) &&
             (current[0]!= fillColor[0] || current[1]!= fillColor[1]  || current[2]!= bColor[2])  )
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

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	
		//glColor3f(0,0,1);
		/*
		glVertex2d(0,240);
		glVertex2d(640,240);
		
		glVertex2d(320,0);
		glVertex2d(320,480);
		
		DDALine(xmax,ymin, xmax, ymax);
		DDALine(xmax,ymax, xmin, ymax);
		DDALine(xmin,ymax, xmin, ymin);
		*/
		
		drawPolygon(arr,n);
		
		glFlush();
		
		BoundryFill(160,110);

		
}

void main(int argc, char** argv){

	printf("\nEnter no of Vertices :");
	scanf("%d", &n);
	
	/*printf("\nEnter xmin :");
	scanf("%d", &xmin);
	printf("\nEnter ymin :");
	scanf("%d", &ymin);
	printf("\nEnter xmax :");
	scanf("%d", &xmax);
	printf("\nEnter ymax :");
	scanf("%d", &ymax);
	*/
	
	for(int i=0; i<n; i++){
		printf("\nEnter x :");
		scanf("%d", &arr[0][i]);
		printf("\nEnter y :");
		scanf("%d", &arr[1][i]);
	}	
	arr[0][n] = arr[0][0];
	arr[1][n] = arr[1][0];
	
	
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	glutCreateWindow("CG");
	
	glClearColor(1,1,1,0);
	glColor3f(bColor[0],bColor[1], bColor[2]);
	
	gluOrtho2D(0,640,0,480);
	
	glutDisplayFunc(draw);
	glutMainLoop();
	

}
