#include<iostream>
#include<vector>
#include<GL/glut.h>
using namespace std;

vector<vector<float>> input(3, vector<float>(10,0));
vector<vector<float>> scale(3, vector<float>(3,0));
vector<vector<float>> output(3, vector<float>(10,0));
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
    glColor3f(0,0,1);
        glVertex2d(-320,0);
        glVertex2d(320,0);

        glVertex2d(0,-240);
        glVertex2d(0,240);

       glColor3f(0,1,0);
        render(input,v);
        render(output,v);

    glEnd();
    glFlush();
}

void multiply(vector<vector<float>> &inp, vector<vector<float>> &sc, vector<vector<float>> &out, int v){

    for(int i=0; i<3; i++){
        for(int j=0; j<v; j++){
            for(int k=0; k<3; k++){
                out[i][j] += sc[i][k] * inp[k][j];
            }
        } 
    }
    out[0][v] = out[0][0];
    out[1][v] = out[1][0];
}

int main(int argc, char** argv){
    
    int xf,yf;
    float sx,sy;

    cout<<"Enter no. of Vertex :";
    cin>>v;

    for(int i=0; i<v; i++){
        cout<<"\nEnter X :";
        cin>>input[0][i];
        cout<<"Enter Y :";
        cin>>input[1][i];

        input[2][i]=1;
    }

    input[0][v] = input[0][0];
    input[1][v] = input[1][0];
    input[2][v] = input[2][0];

    cout<<"\nInput matrix :\n";
    for(int j=0; j<3; j++){
        for(int k=0; k<=v; k++){
               cout<<input[j][k]<<" ";
        }
        cout<<"\n";
    }

    cout<<"\nEnter Sx :";
    cin>>sx;
    cout<<"\nEnter Sy :";
    cin>>sy;
    cout<<"\nEnter xf :";
    cin>>xf;
    cout<<"\nEnter yf :";
    cin>>yf;

    scale={  {sx, 0, (xf*(1-sx))},
             {0, sy, (yf*(1-sy))},
             {0,  0,     1      }  };
    cout<<"\nScaling matrix :\n";
    for(int j=0; j<3; j++){
        for(int k=0; k<3; k++){
               cout<<scale[j][k]<<" ";
        }
        cout<<"\n";
    }

    multiply(input, scale, output, v);

    cout<<"Result matrix :\n";
    for(int j=0; j<3; j++){
        for(int k=0; k<=v; k++){
               cout<<output[j][k]<<" ";
        }
        cout<<"\n";
    }

     glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutCreateWindow("Translation");
    glClearColor(0,0,0,0);
    glColor3f(0,0,1);
    gluOrtho2D(-320,320,-240,240);
    glutDisplayFunc(draw);

    glutMainLoop();
    

    return 0;
}