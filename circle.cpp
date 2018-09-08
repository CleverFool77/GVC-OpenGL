#include <GL/glut.h>
#include <math.h>
#include<GL/gl.h>

struct Point {
	GLint x;
	GLint y;
};

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
void display(void) {
	Point p1 = {350,350};
	 GLint length = 100;

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		draw_circle(p1, length);
		
	glEnd();
	glFlush();
}


int main(int argc, char** argv)  
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(700, 600);
	glutInitWindowPosition(150, 200);
	glutCreateWindow("It's a circle");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
