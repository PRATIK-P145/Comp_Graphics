#include<iostream>
#include<vector>
#include<GL/glut.h>
using namespace std;

vector<vector<float>> input(2, vector<float>(10,0));
vector<vector<float>> scale(2, vector<float>(2,0));
vector<vector<float>> output(2, vector<float>(10,0));
int v;

void render(vector<vector<float>> &arr,int v ){
    for(int i=0; i<v; i++){
        glVertex2f(arr[0][i],arr[1][i]);
        glVertex2f(arr[0][i+1],arr[1][i+1]);
    } 
}

void draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
        glVertex2d(-320,0);
        glVertex2d(320,0);

        glVertex2d(0,-240);
        glVertex2d(0,240);

        render(input,v);
        render(output,v);

    glEnd();
    glFlush();
}

void multiply(vector<vector<float>> &inp, vector<vector<float>> &sc, vector<vector<float>> &out, int v){

    for(int i=0; i<2; i++){
        for(int j=0; j<v; j++){
            for(int k=0; k<2; k++){
                out[i][j] += sc[i][k] * inp[k][j];
            }
        }
    }
    out[0][v] = out[0][0];
    out[1][v] = out[1][0];
}

int main(int argc, char** argv){
    
    //int v;
    float sx,sy;

    cout<<"Enter no. of Vertex :";
    cin>>v;

    for(int i=0; i<v; i++){
        cout<<"\nEnter X :";
        cin>>input[i][0];
        cout<<"Enter Y :";
        cin>>input[i][1];

        input[i][2]=1;
    }

    cout<<"\nEnter Sx :";
    cin>>sx;
    cout<<"\nEnter Sx :";
    cin>>sy;

    scale = {{sx,0},{0,sy}};

    multiply(input, scale, output, v);

    cout<<"Result matrix :\n";
    for(int j=0; j<3; j++){
        for(int k=0; k<v; k++){
               cout<<output[j][k]<<" ";
        }
        cout<<"\n";
    }


    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutCreateWindow("Translation");
    glClearColor(0,0,0,0);
    glColor3f(0,1,0);
    gluOrtho2D(-320,320,-240,240);
    glutDisplayFunc(draw);

    glutMainLoop();

    

    return 0;
}