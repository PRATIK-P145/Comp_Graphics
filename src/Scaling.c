#include<stdio.h>
#include<GL/glut.h>


int inp[3][10];
int out[3][10];
float sc[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 1}};
int v,xf,yf;
float sx, sy;

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glColor3f(0,0,1);
	glVertex2d(320,0);
	glVertex2d(-320,0);
	
	glVertex2d(0,240);
	glVertex2d(0,-240);
	
	glColor3f(0,1,0);
	for(int i=0; i<v; i++){
		glVertex2d(inp[0][i],inp[1][i]); 
		glVertex2d(inp[0][i+1],inp[1][i+1]);
	}
	
	for(int i=0; i<v; i++){
		glVertex2d(out[0][i],out[1][i]); 
		glVertex2d(out[0][i+1],out[1][i+1]);
	}
		
	
	glEnd();
	glFlush();
}



void multiply(){
	
	for(int i=0; i<3; i++){
		 for(int j=0; j<v; j++){
		 	out[i][j] = 0;
		 	for(int k=0; k<3; k++){
		 		out[i][j] = out[i][j] + sc[i][k]*inp[k][j];
		 	}
		 }
	}
	out[0][v] = out[0][0];
	out[1][v] = out[1][0];
	out[2][v] = 1;
	
}

void main(int argc, char** argv){



	printf("Enter no. of Vertices :");
	scanf("%d",&v);
	//printf("Enter no. of Vertices %d:",v);
	
	int i;
	for(i=0; i<v; i++){
		printf("Enter x%d :",i+1);
		scanf("%d",&inp[0][i]);
		
		printf("Enter y%d :",i+1);
		scanf("%d",&inp[1][i]);
		
		inp[2][i]=1;
	}
	inp[0][v] = inp[0][0];
	inp[1][v] = inp[1][0];
	inp[2][v]=1;
	
	
	
	printf("\nInput Matrix :\n");
	
	for(int i=0; i<3; i++){
		for(int j=0; j<v; j++){
			printf("%d ", inp[i][j]);
		}
		printf("\n");
	}
	
	
		printf("Enter sx :");
		scanf("%f",&sx);
		printf("Enter sy :");
		scanf("%f",&sy);
		
		printf("Enter xf :");
		scanf("%d",&xf);
		printf("Enter yf :");
		scanf("%d",&yf);
		
		//float sc[3][3] = { {sx, 0, xf*(1-sx)}, {0, sy, yf*(1-sy)}, {0, 0, 1}};
		sc[0][0] = sx;
		sc[1][1] = sy;
		sc[0][2] = xf*(1-sx);
		sc[1][2] = yf*(1-sy);
		
	printf("\nScaling Matrix :\n");
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			printf("%f ", sc[i][j]);
		}
		printf("\n");
	}
	
	multiply();
	
	
	printf("\nOutput Matrix:\n");
	for(int i=0; i<3; i++){
		for(int j=0; j<v; j++){
			printf("%d ", out[i][j]);
		}
		printf("\n");
	}
	
	
	
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	glutCreateWindow("Scaling");
	
	glClearColor(0,0,0,0);
	glColor3f(0,0,1);
	
	gluOrtho2D(-320,320,-240,240);
	
	glutDisplayFunc(draw);
	glutMainLoop();

	return;
}
