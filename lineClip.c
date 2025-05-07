#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>

int xmin,ymin,xmax,ymax;

struct ver{
float x,y;
int outcode[4];
}p1,p2,orig1,orig2;

int ROUND(float a){
return(int)(a+0.5);
}

void DDA(int xa,int ya,int xb,int yb){
int dx,dy,steps;
dx=xb-xa;
dy=yb-ya;

if(abs(dx)>abs(dy)){
steps=abs(dx);
} else {
steps=abs(dy); 
}

glVertex2d(xa,ya);
float xinc,yinc;
xinc=(float)dx/steps;
yinc=(float)dy/steps;

float x=xa,y=ya;
for(int i=0;i<steps;i++){
x+=xinc;
y+=yinc;
glVertex2d(ROUND(x),ROUND(y));
}
}

void calculate(struct ver *p){
for(int i=0;i<4;i++){
p->outcode[i]=0;
}

if(p->x < xmin){
p->outcode[3]=1;
}
if(p->x > xmax){
p->outcode[2]=1;
}
if(p->y < ymin){
p->outcode[1]=1;
}
if(p->y > ymax){
p->outcode[0]=1;
}

for(int j=0;j<4;j++){
printf("%d",p->outcode[j]);
}
}

void WindowClipping(){
calculate(&p1);
printf("\n");
calculate(&p2);

orig1=p1;
orig2=p2;

int flag1=0;
for(int i=0;i<4;i++){
if(p1.outcode[i]==1 || p2.outcode[i]==1){
flag1=1;
break;
}
}

if(flag1==0){
printf("\nFully Accepted");
} else {
int flag2=0;
for(int j=0;j<4;j++){
if(p1.outcode[j] & p2.outcode[j]){  // Partially Accepetd
flag2=1;
}
}

if(flag2==1){
printf("\nFully Rejected");
return;
} else{
printf("\nPartially Rejected");
float m=(orig2.y-orig1.y)/(orig2.x-orig1.x);
printf(" | Slope: %f",m);

if(p1.outcode[3]){
p1.x=xmin;
p1.y=orig1.y+m*(xmin-orig1.x);
} 
if(p1.outcode[2]){
p1.x=xmax;
p1.y=orig1.y+m*(xmax-orig1.x);
} 
if(p1.outcode[1]){
p1.y=ymin;
p1.x=orig1.x+(ymin-orig1.y)/m;
}
if(p1.outcode[0]){
p1.y=ymax;
p1.x=orig1.x+(ymax-orig1.y)/m;
}

if(p2.outcode[3]){
p2.x=xmin;
p2.y=orig2.y+m*(xmin-orig2.x);
} 
if(p2.outcode[2]){
p2.x=xmax;
p2.y=orig2.y+m*(xmax-orig2.x);
} 
if(p2.outcode[1]){
p2.y=ymin;
p2.x=orig2.x+(ymin-orig2.y)/m;
}
if(p2.outcode[0]){
p2.y=ymax;
p2.x=orig2.x+(ymax-orig2.y)/m;
}
}
}

printf("\nNew Coordinates: (%.2f,%.2f)->(%.2f,%.2f)",p1.x,p1.y,p2.x,p2.y);
DDA(ROUND(p1.x),ROUND(p1.y),ROUND(p2.x),ROUND(p2.y));
}

void Draw(){
glClear(GL_COLOR_BUFFER_BIT);

glColor3f(0,0,1);
glBegin(GL_POINTS);
DDA(xmin,ymin,xmax,ymin);
DDA(xmax,ymin,xmax,ymax);
DDA(xmax,ymax,xmin,ymax);
DDA(xmin,ymax,xmin,ymin);
glEnd();

glColor3f(1,0,0);
glBegin(GL_POINTS);
DDA(ROUND(p1.x),ROUND(p1.y),ROUND(p2.x),ROUND(p2.y));
glEnd();

glColor3f(0,0,0);
glBegin(GL_POINTS);
WindowClipping();
glEnd();
glFlush();
}

int main(int argc,char **argv){

        printf("Enter xmin):");
    scanf("%d", &xmin);
    printf("\nEnter ymin):");
    scanf("%d", &ymin);
    printf("\nEnter xmax):");
    scanf("%d", &xmax);
    printf("\nEnter ymax):");
    scanf("%d", &ymax);



    printf("\nEnter (x1):");
    scanf("%f", &p1.x);
    printf("\nEnter (y1):");
    scanf("%f", &p1.y);
    printf("\nEnter (x2):");
    scanf("%f", &p2.x);
    printf("\nEnter (y2):");
    scanf("%f", &p2.y);

glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(640,480);
glutInitWindowPosition(0,0);
glutCreateWindow("Amey");
glClearColor(1,1,1,0);
gluOrtho2D(0,640,0,480);
glutDisplayFunc(Draw);
glutMainLoop();
return 0;
}
