#include <stdio.h>
#include <GL/glut.h>
#include<math.h>

int xa = 150, ya = 150;
int xmin,ymin, xmax, ymax;
int accepted = 1;
int PA=1;
int clipx1,clipy1,clipx2,clipy2;
int outcode1[4] = {};
int outcode2[4] = {};

float brdrCol[3]={0.0, 1.0, 0.0};

float cyan[3] = {0.0, 1.0, 1.0};
float yellow[3] = {1.0, 1.0, 0.0};
float magenta[3] = {1.0, 0.0, 1.0};
float green[3] = {0.0, 1.0, 0.0};
float white[3] = {1.0, 1.0, 1.0};

void gen_Outcode(int x, int y, int outcode[4]){
    if(x<xmin){
        outcode[2] = 1;
    }
    if(x>xmax){
        outcode[3] = 1;
    }
    if(y< ymin){
        outcode[1] = 1;
    }
    if(x > ymax){
        outcode[0] = 1;
    }
}

void line_clip(int xa, int ya, int xb, int yb){
    gen_Outcode(xa,ya,outcode1);
    gen_Outcode(xb,yb,outcode2);

    for(int i=0; i<4; i++){
        if(outcode1[i]==1 || outcode2[i]==1 ){
            accepted = 0;
            break;
        }
    }

    if(!accepted){
        for(int i=0; i<4; i++){
            if((outcode1[i] & outcode2[i])== 1 ){
                PA = 0;
                break;
            }
        }
        
        if(PA){
            float slope,exp;
  
            if(xb==xa){
                slope = 1;
                exp = 0;

            }else{
                float slope = (float)(yb-ya)/(xb-xa);
                exp = (float)(yb-ymin)/slope;
            }
            //for point 1
            if(outcode1[3]==1 || outcode1[2]==1){
				if(outcode1[3]==1){
					clipy1 = ymax;
				}else{
					clipy1 = ymin;
				}
                clipx1 = xb - exp;
            }
            if(ya>ymax){
                clipx1 = xb - exp;
                clipy1 = ymin;
            }
            //for point 2
            if(ya<ymin){
                clipx1 = xb - exp;
                clipy1 = ymin;
            }
            if(ya>ymax){
                clipx1 = xb - exp;
                clipy1 = ymin;
            }
            
        }

    }


}

void BoundryFill(int x, int y, float brdrCol[3], float fillCol[3]){
	float current[3];
	glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, current);

	if( (current[0]!=brdrCol[0] || current[1]!=brdrCol[1] || current[2]!=brdrCol[2]) &&
	    (current[0]!=fillCol[0] || current[1]!=fillCol[1] || current[2]!=fillCol[2] ) ){
		glColor3f( fillCol[0], fillCol[1], fillCol[2]);
        glBegin(GL_POINTS);
		glVertex2d(x,y);
        glEnd();
        glFlush();
	
	BoundryFill(x+1, y, brdrCol, fillCol);
	BoundryFill(x-1, y, brdrCol, fillCol);
	BoundryFill(x, y+1, brdrCol, fillCol);
	BoundryFill(x, y-1, brdrCol, fillCol);
    }
}

void plotPixel(int xc, int yc, int x, int y){

	glVertex2d(xc+x, yc+y);
	glVertex2d(xc+x, yc-y);
	glVertex2d(xc-x, yc+y);
	glVertex2d(xc-x, yc-y);

	glVertex2d(xc+y, yc+x);
	glVertex2d(xc+y, yc-x);
	glVertex2d(xc-y, yc+x);
	glVertex2d(xc-y, yc-x);

	glFlush();

}

void BresCircle(int xc, int yc, int r){
	int d,x = 0, y = r;
	
	d = 3 - 2*r;

	while(y>=x){
		plotPixel(xc,yc,x,y);

		if(d<0){
			d = d + 4*x + 6;
		}else{
			d = d + 4*x - 4*y + 15;
			y--;
		}
		x++;
	}
}

void BresLine(int xa, int ya, int xb, int yb){
	int d,x,y,f;
	int dx = xb - xa;
	int dy = yb - ya;

	if(abs(dx) > abs(dy)){
		d = 2*abs(dy) - abs(dx);

		if(dx>0){
			x = xa; y = ya; f = xb;
		}else{
			x = xb; y = yb; f = xa;
		}

		while(f>x){
			if(d<0){
				d += 2*abs(dy);

			}else{
				d += 2*abs(dy) - 2*abs(dx);

				if(dx>0 && dy>0 || dx<0 && dy<0){
					y++;
				}else{
					y--;

				}
			}
			glVertex2d(x,y);
			x++;
		}

	}else{
		d = 2*abs(dx) - abs(dy);

		if(dy>0){
			x = xa; y = ya; f = yb;
		}else{
			x = xb; y = yb; f = ya;
		}

		while(f>y){
			if(d<0){
				d += 2*abs(dx);

			}else{
				d += 2*abs(dx) - 2*abs(dy);

				if(dx>0 && dy>0 || dx<0 && dy<0){
					x++;
				}else{
					x--;

				}
			}
			glVertex2d(x,y);
			y++;
		}

	}

}



void legs(int xa, int ya){
	BresLine(xa,ya, xa+50,ya);
	BresLine(xa+50,ya, xa+50,ya-100);
	BresLine(xa+50,ya-100, xa,ya-100);
	BresLine(xa,ya-100, xa,ya);

}

void rectangle(int xmin, int ymin, int xmax, int ymax){
	BresLine(xmin,ymin, xmax,ymin);
	BresLine(xmax,ymin, xmax, ymax);
	BresLine(xmax, ymax, xmin, ymax);
	BresLine(xmin, ymax, xmin, ymin);
	
}

void mouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        int normy = 480-y;
        printf("%d , %d \n",x,normy);
    }
}



void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_POINTS);

	    // BODY
	BresLine(xa, ya, xa+150,ya);
	BresLine(xa+150, ya, xa+150,ya+200);
	BresLine(xa+150, ya+200, xa,ya+200);
	BresLine(xa, ya+200, xa,ya);

		// LEGS
	legs(xa,ya);
	legs(xa+100, ya);

		// HANDS
	BresLine(xa, ya+200, xa-50, ya+120);
	BresLine(xa-50, ya+120, xa, ya+150);
	BresLine(xa, ya+150, xa, ya+200);

    BresLine(xa+150, ya+200, xa+200, ya+120);
	BresLine(xa+200, ya+120, xa+150, ya+150);
	BresLine(xa+150, ya+150, xa+150, ya+200);

        //NECK
        BresLine(xa+60, ya+200, xa+60, ya+213);
        BresLine(xa+90, ya+200, xa+90, ya+213);

	// Face
	BresCircle(xa+75,ya+260,50);

	//MOUTH
	rectangle(xa+50, ya+230, xa+100, ya+240);

    BresCircle(xa+50,ya+270,10);
    BresCircle(xa+100,ya+270,10);

    BresLine(xa+75, ya+270, xa+65, ya+250);
    BresLine(xa+75, ya+270, xa+85, ya+250);
    BresLine(xa+85, ya+250, xa+65, ya+250);

    glColor3f(1,0,0);
  //  rectangle(270,200,330,260);

    glEnd();

	glFlush();

// 	BoundryFill(xa+25, ya-50, brdrCol, cyan); // fill leg2
//     BoundryFill(xa+120, ya-50, brdrCol, cyan); // Fill leg2

//    BoundryFill(xa-10, ya+180, brdrCol, magenta); // hand1
//    BoundryFill(xa+180, ya+150, brdrCol, magenta); // hand2

//      BoundryFill(xa+75, ya+280, brdrCol, yellow);  // face
// 	 BoundryFill(xa+50, ya+270, brdrCol, white);
// 	 BoundryFill(xa+100, ya+270, brdrCol, white);

//    BoundryFill(xa+10, ya+10, brdrCol, green); // body

	


}

int main(int argc , char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("CG Lab");

    glClearColor(0,0,0,0);
    glColor3f(0,1,0);

    gluOrtho2D(0,640,0,480);

    glutDisplayFunc(draw);
	glutMouseFunc(mouse);
   
    glutMainLoop();




    return 0;
}