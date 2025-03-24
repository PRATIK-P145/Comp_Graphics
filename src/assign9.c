#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
int xa,ya,xb,yb;
int v;
float ref[3][3],xshear[3][3],yshear[3][3],rotate[3][3],scale[3][3],tr[3][3],input[3][10],output[3][10];

void mul(float input[3][10], float tr[3][3], float output[3][10], int v)
{ 
     for(int i=0;i<3;i++)
    {
        for(int j=0;j<v;j++)
        {  
            output[i][j]=0;
            for(int k=0; k<3;k++)
            {
                output[i][j] += tr[i][k] * input[k][j];
            }
        }
    }
}

void TranslationMatrix()
{
    printf("\nEnter no of Records: ");
    scanf("%d",&v);
   //INput MAtrix 
    for(int i=0;i<v;i++)
    {
        printf("\nX[%d]: ",i);
        scanf("%f",&input[0][i]);
        printf("\nY[%d]: ",i);
        scanf("%f",&input[1][i]);
        input[2][i]=1;
    }
    printf("\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<v;j++)
        {
            printf("\t%f",input[i][j]);
        }
        printf("\n");
    }
    
    //Translation MAtrix
    float tx,ty;
    printf("\nEnter tx: ");
    scanf("%f",&tx);
    
    printf("\nEnter ty: ");
    scanf("%f",&ty);
    for(int i=0;i<3;i++)
    {
      for(int j=0;j<3;j++)
      {
          if(i==j)
          {
            tr[i][j]=1;
          }
          else
          {
            tr[i][j]=0;
          }
      }
    }
    tr[0][2]=tx;
    tr[1][2]=ty;
     printf("\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("\t%f",tr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //output matrix
    mul(input,tr,output,v);
    
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<v;j++)
        {
            printf("\t%f",output[i][j]);
        }
        printf("\n");
    }
    
}

void ScaleMatrix()
{
    printf("\nEnter no of Records: ");
    scanf("%d",&v);
   //INput MAtrix 
    for(int i=0;i<v;i++)
    {
        printf("\nX[%d]: ",i);
        scanf("%f",&input[0][i]);
        printf("\nY[%d]: ",i);
        scanf("%f",&input[1][i]);
        input[2][i]=1;
    }
    printf("\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<v;j++)
        {
            printf("\t%f",input[i][j]);
        }
        printf("\n");
    }
    
    //Scaling MAtrix
    int xf,yf;
    float sx,sy;
    printf("\nEnter value of Sx & Sy: ");
    scanf("%f%f",&sx,&sy);
    
    printf("\nEnter Fixed Point Xf & Yf: ");
    scanf("%d%d",&xf,&yf);
    
    scale[0][0]=sx;
    scale[0][1]=0;
    scale[0][2]=xf * (1 - sx);
    
    scale[1][0]=0;
    scale[1][1]=sy;
    scale[1][2]=yf * (1 - sy);
    
    scale[2][0]=0;
    scale[2][1]=0;
    scale[2][2]=1;
    
    printf("\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("\t%f",scale[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //output matrix
    mul(input,scale,output,v);
    
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<v;j++)
        {
            printf("\t%f",output[i][j]);
        }
        printf("\n");
    }
    
}
float radian(float a)
{
    return(a * (3.14/180));
}
void RotationMatrix()
{
    printf("\nEnter no of Records: ");
    scanf("%d",&v);
   //INput MAtrix 
    for(int i=0;i<v;i++)
    {
        printf("\nX[%d]: ",i);
        scanf("%f",&input[0][i]);
        printf("\nY[%d]: ",i);
        scanf("%f",&input[1][i]);
        input[2][i]=1;
    }
    printf("\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<v;j++)
        {
            printf("\t%f",input[i][j]);
        }
        printf("\n");
    }
    
    //Rotation MAtrix
    int xr,yr;
    float t;
    printf("\nEnter value of Angle: ");
    scanf("%f",&t);
    
    printf("\nEnter Fixed Point Xr & Yr: ");
    scanf("%d%d",&xr,&yr);
    
    rotate[0][0]=cos(radian(t));
    rotate[0][1]=-sin(radian(t));
    rotate[0][2]=xr * (1 - cos(radian(t))) + yr * sin(radian(t));
    
    rotate[1][0]=sin(radian(t));
    rotate[1][1]=cos(radian(t));
    rotate[1][2]=yr * (1 - cos(radian(t))) - xr * sin(radian(t));
    
    rotate[2][0]=0;
    rotate[2][1]=0;
    rotate[2][2]=1;
    
    printf("\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("\t%f",rotate[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //output matrix
    mul(input,rotate,output,v);
    
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<v;j++)
        {
            printf("\t%f",output[i][j]);
        }
        printf("\n");
    }
    
}
void ShearMatrix()
{   
    int ch;
    printf("\n1.X shear\n2.Y shear\nEnter Choice: ");
    scanf("%d",&ch);
    printf("\nEnter no of Records: ");
    scanf("%d",&v);
   //INput MAtrix 
    for(int i=0;i<v;i++)
    {
        printf("\nX[%d]: ",i);
        scanf("%f",&input[0][i]);
        printf("\nY[%d]: ",i);
        scanf("%f",&input[1][i]);
        input[2][i]=1;
    }
    printf("\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<v;j++)
        {
            printf("\t%f",input[i][j]);
        }
        printf("\n");
    }
    
    
    float xref,yref;
    float shx,shy;
    switch(ch)
    {
        case 1:{
    printf("\nEnter value of X shear: ");
    scanf("%f",&shx);
    
    printf("\nEnter Value of Yref: ");
     scanf("%f",&yref);
      xshear[0][0]=1;  
      xshear[0][1]=shx;
      xshear[0][2]=-shx*yref;
    
    xshear[1][0]=0;
    xshear[1][1]=1;
    xshear[1][2]=0;
    
    xshear[2][0]=0;
    xshear[2][1]=0;
    xshear[2][2]=1;
    
    printf("\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("\t%f",xshear[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //output matrix
    mul(input,xshear,output,v);
    
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<v;j++)
        {
            printf("\t%f",output[i][j]);
        }
        printf("\n");
    }
    }
      break;
      
      case 2:{
              
    printf("\nEnter value of Y shear: ");
    scanf("%f",&shy);
    
    printf("\nEnter Value of xref: ");
     scanf("%f",&xref);
      yshear[0][0]=1;  
      yshear[0][1]=0;
      yshear[0][2]=0;
    
    yshear[1][0]=shy;
    yshear[1][1]=1;
    yshear[1][2]=-shy*xref;
    
    yshear[2][0]=0;
    yshear[2][1]=0;
    yshear[2][2]=1;
    
    printf("\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("\t%f",yshear[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //output matrix
    mul(input,yshear,output,v);
    
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<v;j++)
        {
            printf("\t%f",output[i][j]);
        }
        printf("\n");
    }
            }
            break;
    
    }
}

void ReflectionMatrix()
{   
     int ch=0;
     printf("\n1.Reflection about X-axis\n2.Reflection about Y-axis\n3.Reflection to an Axis Perpendicular to xy plane\n4.Reflection about Y=X\n5.Reflection about Y=-X\nEnter Choice:");
     scanf("%d",&ch);
     
    printf("\nEnter no of Records: ");
    scanf("%d",&v);
   //INput MAtrix 
    for(int i=0;i<v;i++)
    {
        printf("\nX[%d]: ",i);
        scanf("%f",&input[0][i]);
        printf("\nY[%d]: ",i);
        scanf("%f",&input[1][i]);
        input[2][i]=1;
    }
    printf("\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<v;j++)
        {
            printf("\t%f",input[i][j]);
        }
        printf("\n");
    }
    
    //ReflectionMAtrix
    
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(i==j)
            {
              ref[i][j]=1;
            }
            else
            {
              ref[i][j]=0;
            }
        }
    }

    switch(ch)
    {
        case 1:
        ref[1][1]=-1;
        break;
        
        case 2:
        ref[0][0]=-1;
        break;
        
        case 3:
         ref[1][1]=-1;
         ref[0][0]=-1;
        break;
        
        case 4:
        ref[0][0]=0;
        ref[1][1]=0;
        ref[0][1]=1;
        ref[1][0]=1;
        break;
        
        case 5:
        ref[0][0]=0;
        ref[1][1]=0;
        ref[0][1]=-1;
        ref[1][0]=-1;
        break;
    }
    
    printf("\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("\t%f",ref[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    mul(input,ref,output,v);
    
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<v;j++)
        {
            printf("\t%f",output[i][j]);
        }
        printf("\n");
    }
    
}


int ROUND(float a)
{
    return (int) (a+0.5);
}

void DDAL(int xa,int ya,int xb, int yb)
{
    int dx,dy,steps;
    dx=xb-xa;
    dy=yb-ya;
    
    if(abs(dx)>abs(dy))
    {
        steps=abs(dx);
    }
    else
    {
        steps=abs(dy);
    }
    
    glVertex2d(xa,ya);
    float xinc,yinc;
    xinc=(float)dx/steps;
    yinc=(float)dy/steps;
    
    float x=xa,y=ya;
    for(int i=0;i<steps;i++)
    {
        x=x+xinc;
        y=y+yinc;
        glVertex2d(ROUND(x),ROUND(y));
    }
}

void Draw()
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    DDAL(-320,0,320,0);
    DDAL(0,-240,0,240);
    for(i=0;i<v-1;i++)
    {
        DDAL(input[0][i],input[1][i],input[0][i+1],input[1][i+1]);
    }
        DDAL(input[0][i],input[1][i],input[0][0],input[1][0]);
    glEnd();
    glFlush();
    
    usleep(500000);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    DDAL(-320,0,320,0);
    DDAL(0,-240,0,240);
    for(i=0;i<v-1;i++)
    {
        DDAL(output[0][i],output[1][i],output[0][i+1],output[1][i+1]);
    }
        DDAL(output[0][i],output[1][i],output[0][0],output[1][0]);
    glEnd();
    glFlush();
}


int main(int argc,char **argv)
{

    int c;
    printf("\n1.Translation\n2.Scaling\n3.Rotation\n4.Shear\n5.Reflection\nEnter Choice: ");
    scanf("%d",&c);
    switch(c)
    {
        case 1:
        TranslationMatrix();
        break;
      
        case 2:
        ScaleMatrix();
        break;
       
        case 3:
        RotationMatrix();
        break;
        
        case 4:
        ShearMatrix();
        break;
        
        case 5:
        ReflectionMatrix();
        break;
        
    }
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("Translation");
    glClearColor(1,1,1,0);
    glColor3f(0,0,0);
  gluOrtho2D(-320,320,-240,240);
    glutDisplayFunc(Draw);
    glutMainLoop();
    
    return 0;
}
