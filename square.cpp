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

void init() {  
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 700, 0, 600);
}

void draw_square(Point p1,GLint length)
	{
       
	Point p2;
        p2.x = p1.x+length;
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
	Point p1 = {100, 100};
	 GLint length = 300;

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		draw_square(p1, length);
		
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
