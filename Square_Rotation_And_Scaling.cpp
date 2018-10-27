#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define SIN(x) sin(x * 3.141592653589/180)
#define COS(x) cos(x * 3.141592653589/180)

struct Point{
	GLint x;
	GLint y;	
};

float angle = 0;
Point p1 = {200, 200};
Point ori = {200,200};
GLint side = 20;
GLint side2 = 10;
GLint scale = 1;
GLint MAX = 800;
GLint MIN = 2;


void myinit(){
    glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 700, 0, 700);
}

Point initstruct(int a,int b){
    Point p;
    p.x = a;
    p.y = b;
    return p;
}

Point scaling(Point p, GLfloat s){
	Point p1;
	p1.x = p.x*s;
	p1.y = p.y*s;
	return p1;
}

Point rotating(Point p , GLfloat angle){
	Point p2;
	p2.x = ori.x + (p.x-ori.x)*COS(angle) - (p.y-ori.y)*SIN(angle);   
	p2.y = ori.x + (p.x-ori.y)*SIN(angle) + (p.y-ori.y)*COS(angle);
	return p2; 
}

void dda(Point a, Point b, int fr, int fs){
	GLfloat dx = b.x - a.x;
	GLfloat dy = b.y - a.y;
	GLfloat x1 = a.x;
	GLfloat y1 = a.y;
	GLfloat steps = 0;

	steps = abs(dx) > abs(dy)?abs(dx):abs(dy);
	GLfloat xInc = dx/steps;
	GLfloat yInc = dy/steps;

	for(float i = 1.00; i <= steps; i++) {
		Point t={x1,y1};
		Point t1=rotating(t,angle);
		glVertex2f(t1.x,t1.y);
		x1 += xInc;
		y1 += yInc;
	}
}

void draw_triangle(Point q1){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	Point q2,q3;
	q2.x = q1.x+side2;
	q2.y = q1.y;


	glEnd();
	glFlush();
}

void draw_rect(Point p1, int fr, int fs){       
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	Point p2,p3,p4;

	if(fr==1){
		if(angle+1>360)
			angle = 0;
		else
			angle = angle+1;
	}

	else if(fs==1){
		if(scale==1 && side*2<=MAX){
			side*=2;
		}
		else if(side/2>=MIN){
			side/=2;
		}
		else{
			return;
		}
	}
    
    p2.x = p1.x+side;
	p2.y = p1.y;
	
	p3.x = p1.x+side;
	p3.y = p1.y+side;
	
	p4.x = p1.x;
	p4.y = p1.y+side;

    
    dda(p1,p2,fr,fs);
	dda(p2,p3,fr,fs);
	dda(p4,p3,fr,fs);
	dda(p1,p4,fr,fs);
	glEnd();
	glFlush();
}

void draw_btn(Point p, int fr, int fs){       
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	Point p2,p3,p4;
    
    p2.x = p.x+side;
	p2.y = p.y;
	
	p3.x = p.x+side;
	p3.y = p.y+side;
	
	p4.x = p.x;
	p4.y = p.y+side;

    
    dda(p,p2,fr,fs);
	dda(p2,p3,fr,fs);
	dda(p4,p3,fr,fs);
	dda(p,p4,fr,fs);
	glEnd();
	glFlush();
}


void display(void){
	Point plus = {250,250}, minus={500,0};
	draw_btn(plus,0,0);
	draw_btn(minus,0,0);
	draw_rect(p1,0,0);	
}

void processKeys(unsigned char key, int x, int y){
	switch(key){
		case 'r':
		case 'R':	//printf("%f ",angle);
					draw_rect(p1,1,0);
					break;
		case 's':
		case 'S':	draw_rect(p1,0,1);
					break;
	}
}

void processmouse(int button, int state, int x, int y){
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		if(y>300){
			scale=-1;
		}
		else if(y<300){
			scale=1;
		}
	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("INTERACTIVE PROG");
	myinit();
	glutDisplayFunc(display);	
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processmouse);
	glutMainLoop();

	return 0;
}
