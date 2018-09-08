#include <GL/glut.h>
#include <math.h>
#include<GL/gl.h>

struct Point {
	GLint x;
	GLint y;
};

void draw_line(Point a, Point b) 

{
	GLfloat dx = b.x - a.x;
	GLfloat dy = b.y - a.y;

	GLfloat x1 = a.x;
	GLfloat y1 = a.y;

	GLfloat steps = 0;

	if(abs(dx) > abs(dy)) 
	{
		steps = abs(dx);
	} 

	else 
	{
		steps = abs(dy);
	}

	GLfloat xInc = dx/steps;
	GLfloat yInc = dy/steps;

	for(float i = 1.00; i <= steps; i++) {
		glVertex2f(x1, y1);
		x1 += xInc;
		y1 += yInc;
	}
}

void draw_circle(Point p1,GLint radius)
{
    GLint x = 0;
    GLint y = radius;
    GLint p = 1- radius;

    void callcircle(Point , GLint ,GLint );

    callcircle(p1,x,y);

    while(x <  y)
    {
        x++;
         if(p < 0)
        {
            p += (2*x) + 1;
        }
        else{
            y--;
            p += 2*(x-y) + 1;
        }
        callcircle(p1,x,y);
    }
    
}
void callcircle(Point p, GLint x, GLint y)
{
		glVertex2f(p.x + x, p.y + y);
		glVertex2f(p.x - x, p.y + y);
		glVertex2f(p.x + x, p.y - y);
		glVertex2f(p.x - x, p.y - y);
		glVertex2f(p.x + y, p.y + x);
		glVertex2f(p.x - y, p.y + x);
		glVertex2f(p.x + y, p.y - x);
		glVertex2f(p.x - y, p.y - x);
		
}

void init() {  
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 700, 0, 600);
}

void draw_rect(Point p1,GLint length, GLint length1)
	{
       
	Point p2;
        p2.x = p1.x+length1;
	p2.y = p1.y;
        
        draw_line(p1,p2);

        Point p3;
	p3.x = p2.x;
	p3.y = p2.y + length;

        draw_line(p2,p3);

        Point p4;
        p4.x = p1.x;
	p4.y = p1.y+length;

        draw_line(p4,p3);

        draw_line(p1,p4);
}

void display(void) {
	Point p1 = {60, 60};
	 GLint length = 150;
     GLint length1 = 360;
     GLint length2 = 200;
     GLint length3 = 90;
     Point p2 = {490,60};
     Point p3 = {300,60};
     GLint length4 = 80;
     GLint length5 = 40;
     Point p4 = {60,210};
     Point p6 = {420,210};
     Point p5 = {240,290};
     Point p7 = {535,240};
     GLint radius = 50;

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		draw_rect(p1, length, length1);
        draw_rect(p2, length2, length3);
        draw_rect(p3, length4, length5);
        draw_line(p4,p5);
        draw_line(p5,p6);
		draw_circle(p7, radius);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)  
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(700, 600);
	glutInitWindowPosition(150, 200);
	glutCreateWindow("It's a SQAURE");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
