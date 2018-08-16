#include <GL/glut.h>
#include <math.h>
#include<GL/gl.h>

struct Point {
	GLint x;
	GLint y;
};

void draw_line(Point a, Point b) 

{
	GLfloat dx = abs( a.x - b.x);
	GLfloat dy = abs(a.y -b.y);

        GLint p = 2*dy - dx;
	GLint twody = 2*dy;
	GLint twodydx = 2*(dy - dx);
        GLint x1,y1, Endx;
	

	if(a.x > b.x) 
	{
		x1 = b.x;
		y1 = b.y;
		Endx = a.x;
	} 

	else 
	{
		x1 = a.x;
		y1 = a.y;
		Endx = b.x;
	}
        
       while(x1 <Endx)
	{
         glVertex2f(x1,y1);
	x1++;
	  if(p < 0)
	    p =p + twody;
	  else
		{
		  y1++;
		  p = p + twodydx;
		}
	}
}

void init() {  //copied
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 700, 0, 600);
}


void display(void) {
	Point p1 = {100, 100};
	Point p2 = {350,450}; 

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		draw_line(p1, p2);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)  //copied
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(700, 600);
	glutInitWindowPosition(150, 200);
	glutCreateWindow("Bresenhem Algorithm");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
