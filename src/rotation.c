#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define PI 3.14159265358979323846

float inp[3][10];
float R[3][3]={{0,0,0},{0,0,0},{0,0,1}};
float out[3][10];
int v;

void renderMtx(float arr[][10], int v){
    for(int i=0; i<v; i++){
        glVertex2d(arr[0][i], arr[1][i]);
        glVertex2d(arr[0][i+1], arr[1][i+1]);
    }

}

void draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    glColor3f(0,0,1);
	glVertex2d(320,0); glVertex2d(-320,0);
	
	glVertex2d(0,240); glVertex2d(0,-240);
    
    glColor3f(0,1,0);
    renderMtx(inp, v);

    glColor3f(1,0,0);
    renderMtx(out, v);

    glEnd();
    glFlush();
}

void display(float arr[][10],int v){
    for(int i=0; i<3; i++){
        printf("\n");
        for(int j=0; j<=v; j++){
            printf("%f ", arr[i][j]);
        }
    }

}
void display3(float arr[3][3]){
    for(int i=0; i<3; i++){
        printf("\n");
        for(int j=0; j<3; j++){
            printf("%f ", arr[i][j]);
        }
    }

}

void Multiply(){
    for(int i=0; i<3; i++){
        for(int j=0; j<=v; j++){
            out[i][j] = 0;
            
            for(int k=0; k<3; k++){

                out[i][j] = out[i][j] + R[i][k]*inp[k][j];

            }
        }
    }

}

void main(int argc, char** argv){
    printf("Enter no. of Vertices:");
    scanf("%d",&v);
 
    for(int i=0; i<v; i++){
        printf("\nEnter X%d :",i+1);
        scanf("%f", &inp[0][i]);

        printf("Enter Y%d :",i+1);
        scanf("%f", &inp[1][i]);

        inp[2][i]=1;
    }
    inp[0][v] = inp[0][0];
    inp[1][v] = inp[1][0];
    inp[2][v] = inp[2][0];

    display(inp,v);
  
  
    float deg;
    int xr, yr;
    printf("\nEnter Rotation Angle : ");
    scanf("%f", &deg);
    printf("\nEnter Pivot point Xr : ");
    scanf("%d", &xr);
    printf("\nEnter Pivot point Yr : ");
    scanf("%d", &yr);

    float rad = (deg*PI)/180;
    float R02 = ( xr*(1-cos(rad)) + yr*sin(rad) );
    float R12 = ( yr*(1-cos(rad)) - xr*sin(rad) );

    R[0][0] = cos(rad);  R[0][1] = ((-1)*sin(rad));  R[0][2] = R02;
    R[1][0] = sin(rad);  R[1][1] = cos(rad);         R[1][2] = R12;

    display3(R);

    Multiply();

    display(out,v);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("Rotation");

    gluOrtho2D(-320,320,-240,240);

    glClearColor(0,0,0,0);
    glColor3f(0,1,0);

    glutDisplayFunc(draw);
    glutMainLoop();

}