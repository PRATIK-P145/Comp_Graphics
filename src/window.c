#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>
#define M_PI 3.14159265358979323846

int xa,ya,xb,yb,xc,yc,xd,yd;
float fcol[3]={0,0,0};
float bcol[3]={1,1,1};
int V,input[3][15];
float r[3][3],output[3][15];
void bresl(int xa,int ya,int xb,int yb){

  int dx,dy,d;
  dx=xb-xa;
  dy=yb-ya;
  //glBegin(GL_POINTS);
  int c,r,f;
  if(abs(dx)>abs(dy)){
  d=2*abs(dy)-abs(dx);
  
  if(dx>0){
    c=xa;
    r=ya;
    f=xb;
  }else{
    c=xb;
    r=yb;
    f=xa;
  }
  while(f>=c){
    if(d<0){
      c+=1;
      d=d+2*abs(dy);
    }else{
      c+=1;
      if(dx>0 && dy>0 || dx<0 && dy<0){
        r=r+1;
      }else{
        r=r-1;
      }d=d+2*abs(dy)-2*abs(dx);
    }
    
  glVertex2d(c,r);
  
  }}else{
       d=2*dx-dy;
  if(dy>0){
    c=ya;
    r=xa;
    f=yb;
  }else{
    c=yb;
    r=xb;
    f=ya;
  }
  while(f>=c){
    if(d<0){
      c+=1;
      d=d+2*abs(dx);
    }else{
      c+=1;
      if(dx>0 && dy>0 || dx<0 && dy<0){
        r=r+1;
      }else{
        r=r-1;
      }d=d+2*abs(dx)-2*abs(dy);
    }
  glVertex2d(r,c);
  
 }}
//glEnd();
//glFlush();
}
void mul(float output[3][15],float r[3][3],int input[3][15]){
  for(int i=0;i<3;i++ ){
    for(int j=0;j<2;j++){
      output[i][j]=0;
      for(int k=0;k<3;k++){
        output[i][j]=output[i][j]+r[i][k]*input[k][j];
      }
    }
  }
 /* for(int i=0;i<3;i++){
    for(int j=0;j<2;j++){
      printf("%f\t",output[i][j]);
    }
    printf("\n");
  }*/
}
void Rotation(){
  int x1,y1;
  float angle,rad; 
  
 for(int i=0;i<2;i++){
    printf("Enter the diagonal Coordinates :");
    scanf("%d",&input[0][i]);
    scanf("%d",&input[1][i]);
    input[2][i]=1;
  }
  xa=input[0][0];
  ya=input[1][0];
  xb=input[0][1];
  yb=input[1][1];
  
  x1=(xb-xa)/2;
  y1=(yb-ya)/2;
  int xf=xa+x1;
  int yf=ya+y1;
  angle=45;
  rad=angle*M_PI/180;
  r[0][0]=cos(rad);
  r[0][1]=-sin(rad);
  r[0][2]=xf*(1-cos(rad))+yf*sin(rad);
  r[1][0]=sin(rad);
  r[1][1]=cos(rad);
  r[1][2]=yf*(1-sin(rad))-xf*cos(rad);
  r[2][0]=0;
  r[2][1]=0;
  r[2][2]=1;
  
  mul(output,r,input);
  
}
void floodFill(int x,int y,float fcol[3],float bcol[3])
{
    float current[3];
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,current);
    
    if((current[0]==bcol[0] && current[1]==bcol[1] && current[2]==bcol[2]) && (current[0] != fcol[0] || current[1] != fcol[1] || current[2] != fcol[2]))
    {
        glColor3f(fcol[0],fcol[1],fcol[2]);
        glBegin(GL_POINTS);
        glVertex2d(x,y);
        glEnd();
        glFlush();
        
        floodFill(x,y+1,fcol,bcol);
        floodFill(x,y-1,fcol,bcol);
        floodFill(x+1,y,fcol,bcol);
        floodFill(x-1,y,fcol,bcol);
        
    }
}


void Draw(){
 glClear(GL_COLOR_BUFFER_BIT);
  
  glBegin(GL_POINTS);
  int xinc1,yinc1,xinc,yinc;
  xinc=(xb-xa)/4;
  yinc=(yb-ya)/4;
  
  for(int i=0;i<5;i++){
    bresl(xa+(xinc*i),ya,xa+(xinc*i),yb);
    bresl(xa,ya+(yinc*i),xb,ya+(yinc*i));
 }
  glEnd();
  glFlush();
 
  for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if ((i + j) % 2 == 0) {
                int seedX = xa + i * xinc + xinc/2;
                int seedY = ya + j * yinc + yinc/2;
                floodFill(seedX, seedY, fcol, bcol);
            }
        }
    }

 usleep(2000000);
 xinc1=(xc-yc)/4;
 yinc1=(xc-yc)/4;
 glClear(GL_COLOR_BUFFER_BIT);
 glBegin(GL_POINTS);
  for(int i=0;i<5;i++){
    bresl(xc+(xinc1*i),yc+(yinc1*i),yc+(xinc1*i),xc+(yinc1*i));
    bresl(xc-(xinc1*i),yc+(yinc1*i),yd-(xinc1*i),xc+(yinc1*i));
    //bresl(xa,ya+(yinc*i),xb,ya+(yinc*i));
    }
  glEnd();
  glFlush();
  for(int i=0;i<4;i++){
    floodFill(xc,yc+15+(yinc1*i*2),fcol,bcol);
  }
 for(int i=1;i<3;i++){
    floodFill(xc-(2*xinc1),yc+(2*yinc1*i)+15,fcol,bcol);
  }
 for(int i=1;i<3;i++){
    floodFill(xc+(2*xinc1),yc+(2*yinc1*i)+15,fcol,bcol);
  }
 
}

int main(int argv,char **argc){
   Rotation();
   xc=output[0][0];
  yc=output[1][0];
  xd=output[0][1];
  yd=output[1][1];
   
  glutInit(&argv,argc);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(480,480);
  glutCreateWindow("Chess");
  glClearColor(1,1,1,0);
  glColor3f(0,0,0);
  gluOrtho2D(0,480,0,480);
  glutDisplayFunc(Draw);
  glutMainLoop();


}

