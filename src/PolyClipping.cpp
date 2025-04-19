#include<iostream>
#include<GL/glut.h>
#include<cmath>
using namespace std;

float input[2][15] = {};
int v,step =0;
int i=1 ;
float output[2][15];
int xmin= -150, ymin= -150, xmax=150, ymax=150;
int m = 0;

int ROUND(float a){
    if(a>=0){
         return (int)(a+0.5);
    }else{
        return (int)(a-0.5);
    }
   
}

void DDALine(int xa , int ya , int xb , int yb){
    glBegin(GL_POINTS);
    int dx = xb - xa ;
    int dy = yb - ya ;

    int steps;
    if(abs(dx) > abs(dy)){ steps = abs(dx);}
    else{ steps = abs(dy);}

    float xinc = (float)(dx)/steps;
    float yinc = (float)(dy)/steps;

    glVertex2d(xa,ya);

    float x=xa, y=ya;
    for(int i=1; i<=steps; i++){
        x = x + xinc;
        y = y + yinc;
        glVertex2d(ROUND(x),ROUND(y));
    }
    glEnd();

}
void DDAL(float x1, float y1, float x2, float y2){
    glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
    glEnd();
}

void printMTX(float arr[2][15], int n){
    for(int i=0; i<2; i++){
        for(int j=0; j<=n; j++){
            cout<<" "<<arr[i][j];
        }
        cout<<endl;
    }
}

void render_mtx(float arr[2][15], int n){
    for(int i=0; i<n; i++){
        DDALine(arr[0][i], arr[1][i], arr[0][i+1], arr[1][i+1]);
    }
}

void input_polygon(){
    do{
        printf("\nEnter no. of vertices (max->15):");
        scanf("%d",&v);
    }while(v>15);

    for(int i=0; i<v; i++){
        printf("\nX%d :",i+1);
        scanf("%f",&input[0][i]);
        printf("Y%d :",i+1);
        scanf("%f",&input[1][i]);
    }
    input[0][v] = input[0][0];
    input[1][v] = input[1][0];
    input[2][v] = input[2][0];
        
}

void left_clip(int xa, int ya, int xb, int yb)
{  
    float slope = (float)(yb - ya) / (xb - xa);
    
    if(xa > xmin && xb > xmin)  // In-In
    {   
        output[0][m] = xb;
        output[1][m] = yb;
        m = m + 1;
    }
    else if(xa < xmin && xb > xmin)  // Out-In
    {
        output[0][m] = xmin ;
        output[1][m] = ya + slope * (float)(xmin - xa);

        output[0][m+1] = xb;
        output[1][m+1] = yb;
        
        m = m + 2;
    }
    else if(xa > xmin && xb < xmin)   // In-Out
    {
        output[0][m] = xmin;
        output[1][m] = ya + slope * (float)(xmin - xa);
        
        m = m + 1;
    }
}

void right_clip(int xa, int ya, int xb, int yb){

    float slope = (float)(yb - ya) / (xb - xa);
    
    if(xa < xmax && xb < xmax)  // In-In
    {   
        output[0][m] = xb;
        output[1][m] = yb;
        m = m + 1;
    }
    else if(xa > xmax && xb < xmax)  // Out-In
    {
        output[0][m] = xmax ;
        output[1][m] = ya + slope * (float)(xmax - xa);
        
        output[0][m+1] = xb;
        output[1][m+1] = yb;
        
        m = m + 2;
    }
    else if(xa < xmax && xb > xmax)   // In-Out
    {
        output[0][m] = xmax;
        output[1][m] = ya + slope * (float)(xmax - xa);
        m = m + 1;
    }
}

void bottom_clip(int xa, int ya, int xb, int yb){
    float slope;
    float exp1;

    if(xa == xb){
         exp1 = 0;
    }
    else{
        slope  = (float)(yb - ya) / (xb - xa);
        exp1 = (float)(ymin - ya)/slope;
     }
    
    if(ya > ymin && yb > ymin)  // In-In
    {   
        output[0][m] = xb;
        output[1][m] = yb;
        m = m + 1;
    }
    else if(ya < ymin && yb > ymin)  // Out-In
    {    
        output[0][m] = exp1 + xa;
        output[1][m] = ymin;

        output[0][m+1] = xb;
        output[1][m+1] = yb;
        m = m + 2;
    }
    else if(ya > ymin && yb < ymin)   // In-Out
    {    
        output[0][m] = exp1 + xa;
        output[1][m] = ymin;
        m = m + 1;
    }
}

void top_clip(int xa, int ya, int xb, int yb){
   
    float slope;
    float exp1;

    if(xa == xb){
         exp1 = 0;
    }
    else{
        slope  = (float)(yb - ya) / (xb - xa);
        exp1 = (float)(ymax - ya)/slope;
    }
    
    if(ya < ymax && yb < ymax)  // In-In
    {     
        output[0][m] = xb;
        output[1][m] = yb;
        m = m + 1;
    }
    else if(ya > ymax && yb < ymax)  // Out-In
    {  
        output[0][m] = exp1 + xa;
        output[1][m] = ymax;

        output[0][m+1] = xb;
        output[1][m+1] = yb;

        m = m + 2;
    }
    else if(ya < ymax && yb > ymax)   // In-Out
    {    
        output[0][m] = exp1 + xa;
        output[1][m] = ymax;
        m = m + 1;
    }
}

void clip_polygon(float inp[2][15], float out[2][15]){
    m =0;
    if(step >= 1){
        for(int j = 0; j <v; j++){
            left_clip(inp[0][j], inp[1][j], inp[0][j+1], inp[1][j+1]);
        }
     output[0][m] = output[0][0]; 
     output[1][m] = output[1][0];
    }

    if(step >= 2){
    int i = m;
    m =0;
    for(int j = 0; j <i; j++){
        right_clip(out[0][j], out[1][j], out[0][j+1], out[1][j+1]);
    }
     output[0][m] = output[0][0]; 
     output[1][m] = output[1][0];
    }

    if(step >=3){
    i = m;
    m =0;
    for(int j = 0; j <i; j++){
        bottom_clip(out[0][j], out[1][j], out[0][j+1], out[1][j+1]);
    }
     output[0][m] = output[0][0]; 
     output[1][m] = output[1][0];
    }

    if(step >= 4){
    i = m;
    m =0;
    for(int j = 0; j <i; j++){
        top_clip(out[0][j], out[1][j], out[0][j+1], out[1][j+1]);
    }
     output[0][m] = output[0][0]; 
     output[1][m] = output[1][0];
    }
}

 
void display(){

if(i==1){
   do{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,1,1);
    DDALine(-320,0,320,0);
    DDALine(0,-240,0,240);

    glColor3f(1,0,0);

    DDALine(xmin, ymin, xmax, ymin);
    DDALine(xmax, ymin, xmax, ymax);
    DDALine(xmax, ymax, xmin, ymax);
    DDALine(xmin, ymax, xmin, ymin);


     glColor3f(0,0,1);
     render_mtx(input, v);

        cout<<"\n-Proceed(1/0) :";
        cin>>i;

        step += i;
        clip_polygon(input, output);
        // cout<<"\n step -"<<step;
        glColor3f(0,1,0);
        render_mtx(output, m);

        if(step > 4){
            cout<<"Clipping Ended !";
            step = 0;
            i=0;
        }

        glFlush();
      // glutPostRedisplay();

   }while(i!=0);
    }
    //  glColor3f(0,1,0);
    //  render_mtx(output, m);
    

}

int main(int argc, char** argv){

    // cout<<"\nxmin:";
    // cin>>xmin;
    // cout<<"\nymin:";
    // cin>>ymin;
    // cout<<"\nxmax:";
    // cin>>xmax;
    // cout<<"\nymax:";
    // cin>>ymax;
    
    input_polygon();


    // for(int j = 0; j <v; j++){
    //     right_clip(input[0][j], input[1][j], input[0][j+1], input[1][j+1]);
    // }
    //  output[0][m] = output[0][0]; 
    //  output[1][m] = output[1][0];

    // clip_polygon(input, output, v, m);

    cout<<"\nInput Matrix :\n";
     printMTX(input,v);
     cout<<"\nOutput Matrix :\n";
     printMTX(output,m);

    glutInit (&argc , argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);

    glutCreateWindow("Clipping");

    glClearColor(0.0, 0.0, 0.0, 0);  // Background Color
    glColor3f(0.0,1.0,0.0);         // Pen color

    gluOrtho2D(-320,320,-240,240);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
/*
#include <iostream>

using namespace std;
float output[2][15];
int xmin, ymin, xmax, ymax;
int m = 0;

void leftclip(int xa, int ya, int xb, int yb)
{
    float slope = (float)(yb - ya) / (xb - xa);
    
    if(xa > xmin && xb > xmin)
    {
        output[0][m] = xb;
        output[1][m] = yb;
        m = m + 1;
    }
    
    if(xa < xmin && xb > xmin)
    {
        output[0][m] = xmin ;
        output[1][m] = ya + slope * (float)(xmin - xa);
        output[0][m + 1] = xb;
        output[1][m + 1] = yb;
        m = m + 2;
    }
    
    if(xa > xmin && xb < xmin)
    {
        output[0][m] = xmin;
        output[1][m] = ya + slope * (float)(xmin - xa);
        m = m + 1;
    }
}


int main() {
    
    
    
    cout<<"\nxmin:";
    cin>>xmin;
    cout<<"\nymin:";
    cin>>ymin;
    cout<<"\nxmax:";
    cin>>xmax;
    cout<<"\nymax:";
    cin>>ymax;
    
    int v;
    int input[2][15];
    
    cout<<"\nVertices:";
    cin>>v;
    
    int j;
    for(j = 0; j < v; j++)
    {
        cout<<"\nx:";
        cin>>input[0][j];
        cout<<"\ny:";
        cin>>input[1][j];
    }
    input[0][j] = input[0][0];
    input[1][j] = input[1][0];
    
    
    
    // /*for(int i = 0; i < 2; i++)
    // {
    //     for(int k = 0; k < v + 1; k++)
    //     {
    //         cout<<input[i][k]<<"\t";
    //     }
    //     cout<<"\n";
    // }*/
    
  /*  for(int i = 0; i < v; i++)
    {
        leftclip(input[0][i], input[1][i], input[0][i+1], input[1][i+1]);
    }
    
    for(int i = 0; i < 2; i++)
    {
        for(int k = 0; k < v ; k++)
        {
            cout<<output[i][k]<<"\t";
        }
        cout<<"\n";
    }
*/