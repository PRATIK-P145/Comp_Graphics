#include<stdio.h>
#include<GL/glut.h>

void Bline(int xa,int ya,int xb,int yb){
  int dx = xb-xa;
  int dy = yb-ya;
  int d,x,y,f;
  
   // GENTLE Slope Condition (dx>dy)
  if(abs(dx)>abs(dy)){    
      d = 2*abs(dy)-abs(dx); // Initial Decision Parameter
      
     // swap if inputs are reverse (Right -> Left)
      if(dx>0){   
          x=xa; y=ya; f=xb;
      }
      else{
          x=xb; y=yb; f=xa;
      }
      
      while(f>x){ // Loop until xmin reaches xmax
        // Bresenham condition
        if(d<0){     
            d += 2*abs(dy);
        }
        else{
            // Positive Slope : Incr Y
            if(dx>0 && dy>0 || dx<0 && dy<0) {  
                y=y+1;
            }
            // Negative Slope : Decr Y
            else{    
                y=y-1;
            } 
            d += 2*abs(dy)-2*abs(dx);
        }
        x = x+1;  // always incr X
        glVertex2d(x,y);
      }
  }
//----------------------------------------------------------//
  // SHARP Slope (dy>dx)
  else{
    d = 2*abs(dx)-abs(dy);
      
      if(dy>0){  
          x=xa; y=ya; f=yb;
      }
      else{   // swap if inputs are Reverse i.e. right -> left
          x=xb; y=yb; f=ya;
      }
      
    //Loop until ymin reaches ymax
      while(f>y){

        if(d<0){
            d = d+2*abs(dx);
        }
        else{
            // Positive Slope : Incr X
            if(dx>0 && dy>0 || dx<0 && dy<0){
                x=x+1;
            }
            // Negative Slope : Decr X
            else{
                x=x-1;
            } 
            d=d+2*abs(dx)-2*abs(dy);
        }
        y=y+1; 
        glVertex2d(x,y);
      }
  
  }
  
}


void draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glColor3f(1,0,0);
    Bline(100,100,400,200);
    glColor3f(0,1,0);
    Bline(100,100,200,400);
    glColor3f(0,0,1);
    Bline(100,100,400,50);
    glColor3f(0,1,1);
    Bline(100,100,50,400);
    glEnd();
    glFlush();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(680,460);
    glutCreateWindow("Bres_Line");
    glClearColor(1,1,1,0);
    glColor3f(0,0,0);
    gluOrtho2D(0,680,0,460);
    glutDisplayFunc(draw);
    glutMainLoop();
    
    return 0;

}
