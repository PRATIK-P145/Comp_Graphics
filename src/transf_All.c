#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define PI 3.14159265358979323846

float input[3][10];
float trans[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
float scale[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
float rotate[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
float output[3][10];
int v;
int ex=0,op;


void multiply(float inp[3][10], float t[3][3], float out[3][10], int n){
    
    for(int i=0; i<3; i++){
        for(int j=0; j<n; j++){
            out[i][j] = 0;
            for(int k=0; k<3; k++){
                out[i][j] = out[i][j] + ( t[i][k] * inp[k][j] );
            }
        }
    }
    out[0][n] = out[0][0];
    out[1][n] = out[1][0];
    out[2][n] = out[2][0];

}

void DDALine(float x1, float y1, float x2, float y2){
    glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
    glEnd();
}

void render_mtx(float arr[3][10], int n){
    for(int i=0; i<n; i++){
        DDALine(arr[0][i], arr[1][i], arr[0][i+1], arr[1][i+1]);
    }
}

void copy_mtx(float arr1[3][10], float arr2[3][10], int n){
    for(int i=0; i<3; i++){
        for(int j=0; j<=n; j++){
            arr1[i][j] = arr2[i][j];
        }
    }
}

void scale_mtx(){
    printf("\nEnter Scale-x:");
    scanf("%f",&scale[0][0]);
    printf("\nEnter Scale-y:");
    scanf("%f",&scale[1][1]);
}

void transl_mtx(){
    printf("\nEnter Tx:");
    scanf("%f",&trans[0][2]);
    printf("\nEnter Ty:");
    scanf("%f",&trans[1][2]);
}

void rotation_mtx(){
    float deg;

    printf("\nEnter Rotation Angle : ");
    scanf("%f", &deg);

    float rad = (deg*PI)/180;

    rotate[0][0] = cos(rad);  rotate[0][1] = ((-1)*sin(rad));  
    rotate[1][0] = sin(rad);  rotate[1][1] = cos(rad);         

}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1,0,0);
    DDALine(-320,0,320,0);
    DDALine(0,-240,0,240);

    glColor3f(0,0,1);
    render_mtx(input, v);

    glColor3f(0,1,0);
    render_mtx(output, v);

    glutSwapBuffers();
}

void apply_transformations(int ch){
    switch(ch){
        case 1 : transl_mtx();
            multiply(input, trans, output, v);
            break;

        case 2 : scale_mtx();
            multiply(input, scale, output, v);
            break;
        
        case 3 : rotation_mtx();
            multiply(input, rotate, output, v);
            break;

        case 0 : ex = 1; exit(0);
           break;

        default :  printf("\nInvalid");

    }
    

}

void update(){
    printf("\nSelect 2D Transformation to perform :");
        printf("\n1.Translation");
        printf("\n2.Scaling");
        printf("\n3.Rotation");
        printf("\n0.EXIT");
        printf("\nPress Key Choice :");
        scanf("%d",&op);

        switch(op){
            case 1:apply_transformations(1);
                break;
            case 2:apply_transformations(2);
                break;
            case 3:apply_transformations(3);
                break;
            case 0: apply_transformations(0);
                break;
            default:printf("\nInvalid Choice");
        }
        glutPostRedisplay();

}



// void key_press(unsigned char key, int x, int y){
//     switch(key){
//         case '1':apply_transformations(1);
//             break;
//         case '2':apply_transformations(2);
//             break;
//         case '3':apply_transformations(3);
//             break;
//         case '0': apply_transformations(0);
//             break;
//         default:printf("\nInvalid Choice");
//     }

// }





int main(int argc, char** argv){
    
    printf("\nEnter no. of vertices :");
    scanf("%d",&v);

    for(int i=0; i<v; i++){
        printf("\nX%d :",i+1);
        scanf("%f",&input[0][i]);
        printf("Y%d :",i+1);
        scanf("%f",&input[1][i]);
        input[2][i] = 1;
    }
    input[0][v] = input[0][0];
    input[1][v] = input[1][0];
    input[2][v] = input[2][0];
        
    

    glutInit (&argc , argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);

    glutCreateWindow("2D Transformations ");

    glClearColor(0.0, 0.0, 0.0, 0);  // Background Color
    glColor3f(0.0,1.0,0.0);         // Pen color

    gluOrtho2D(-320,320,-240,240);

    glutDisplayFunc(display);
    //glutKeyboardFunc(key_press);
    glutIdleFunc(update);
    glutMainLoop();



    return 0;
}