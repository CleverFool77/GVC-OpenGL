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
void init() {  //copied
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(1.0);
	//glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-700, 700, -600, 600);
}

Point initstruct(int a,int b)
{
    Point p;
    p.x = a;
    p.y = b;
    return p;
} 
Point scaling(Point p2,GLfloat nooftimes)
{
	Point p3;
	p3.x = p2.x*nooftimes;
	p3.y = p2.y*nooftimes;

	return p3;
}

Point rotating(Point p , GLfloat angle)
{
	Point p2;
	p2.x = 0 + (p.x-0)*cos(angle) - (p.y-0)*sin(angle);   
	p2.y = 0 + (p.x-0)*sin(angle) + (p.y-0)*cos(angle);

	return p2; 
}

void display(void) {
	struct Point s[3];
    int i;
    int a[3][2]={{0,0},{200,0},{0,100}};
    for( i=0;i<3;i++)
    {
        s[i] = initstruct(a[i][0],a[i][1]);
    }
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
			draw_line(s[0],s[1]);
    		draw_line(s[1],s[2]);
    		draw_line(s[0],s[2]);

			s[2] = scaling(s[2],1.5);
			//135 = 2.35
			s[2] = rotating(s[2],2.35);
			draw_line(s[0],s[2]);
			s[1] = scaling(s[1],1.58);
			s[1] = rotating(s[1],2.09);
			draw_line(s[0],s[1]);
			draw_line(s[1],s[2]);

	glEnd();
	glFlush();
}

int main(int argc, char** argv)  //copied
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(700, 600);
	glutInitWindowPosition(150, 200);
	glutCreateWindow("Transfomration");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}