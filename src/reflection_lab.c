#include<stdio.h>
#include<GL/glut.h>


int inp[3][10];

int refx[3][3] = { {1, 0, 0}, {0, (-1), 0}, {0, 0, 1}};

int inpref[3][10];

int v;

void render(int arr[][10], int v){
	for(int i=0; i<v; i++){
		glVertex2d(arr[0][i],arr[1][i]); 
		glVertex2d(arr[0][i+1],arr[1][i+1]);
	}
	

}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glColor3f(0,0,1);
	glVertex2d(320,0);
	glVertex2d(-320,0);
	
	glVertex2d(0,240);
	glVertex2d(0,-240);
	
	glColor3f(0,1,0);
	
	render(inp, v);
	render(inpref, v);
	
	
	
	glEnd();
	glFlush();
}




void  reflect(){
	
	for(int i=0; i<3; i++){
		 for(int j=0; j<v; j++){
		 	inpref[i][j] = 0;
		 	for(int k=0; k<3; k++){
		 		inpref[i][j] = inpref[i][j] + refx[i][k]*inp[k][j];
		 	}
		 }
	}
	inpref[0][v] = inpref[0][0];
	inpref[1][v] = inpref[1][0];
	inpref[2][v] = 1;
	
}

void main(int argc, char** argv){
 /


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
		for(int j=0; j<=v; j++){
			printf("%d ", inp[i][j]);
		}
		printf("\n");
	}
	

		

	reflect();
	
	
	
	printf("\nInput ref Matrix:\n");
	for(int i=0; i<3; i++){
		for(int j=0; j<=v; j++){
			printf("%d ", inpref[i][j]);
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
