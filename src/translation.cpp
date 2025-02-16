#include<iostream>
#include<GL/glut.h>
#include<vector>
using namespace std;

int v =3;

vector<vector<int>> inp(3,vector<int>(10,0));
vector<vector<int>> T(3,vector<int>(3,0));
vector<vector<int>> out(3,vector<int>(10,0));

//using Matrix = array<array<int, 10>, 3>;
//void input(vector<vector<int>> &A,int v){



void render(vector<vector<int>> &arr,int v){
    glBegin(GL_LINES);
    glLineWidth(1.0);
    for(int i=0; i<v; i++){
        glVertex2d(arr[0][i],arr[1][i]);
        glVertex2d(arr[0][i+1],arr[1][i+1]);
    }
    glEnd();
    glFlush();
}
void draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2d(0,-230);
        glVertex2d(0,230);

        glVertex2d(-310,0);
        glVertex2d(310,0);

    glEnd();
    glFlush();

    render(inp,v);
    render(out,v);
}

void display(vector<vector<int>> &arr,int v){
    for(int i=0; i<3; i++){
        for(int j=0; j<v; j++){
            cout<<arr[i][j]<<"  ";
        }
        cout<<endl;
    }

}
void Multiply( vector<vector<int>> &inp,vector<vector<int>> &T,vector<vector<int>> &out, int v){

     for(int i=0; i<3; i++){

        for(int j=0; j<v; j++){

            for(int k=0; k<3; k++){
                out[i][j] += T[i][k] * inp[k][j];
            }
        }
    }
    out[0][v] = out[0][0];
    out[1][v] = out[1][1];
}

int main(int argc, char** argv){
    int tx,ty;

    for(int i=0; i<v; i++){
        cout<<"Enter X:";
        cin>>inp[0][i];
        cout<<"Enter Y:";
        cin>>inp[1][i];
        inp[2][i] = 1;

        inp[0][v] = inp[0][0];
        inp[1][v] = inp[1][1];
    }
    cout<<"\nInput :\n";
    //display(inp,v);



    cout<<"Enter Tx :";
    cin>>tx;
    cout<<"Enter Tx :";
    cin>>ty;
    for(int i=0; i<3; i++){
        for(int j=0; j<v; j++){
            if(i==j){
                T[i][j] = 1;
            }
        }
    }
    T[0][2] = tx;
    T[1][2] = ty;

    cout<<"\nTranslation :\n";
    //display(T,3);

    Multiply(inp,T,out,v);
    cout<<"\nResult :\n";
    //display(out,v);

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