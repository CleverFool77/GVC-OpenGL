#include <GL/glut.h>
#include <math.h>
#include<GL/gl.h>

struct Point {
	GLint x;
	GLint y;
};

void draw_ellipse(Point p1, GLint rx , GLint ry)
{
    GLint rx2 = rx*rx;
    GLint ry2 = ry*ry;
    GLint tworx2 = 2*rx2;
    GLint twory2 = 2*ry2;
    GLint p,x = 0,y = ry;
    GLint px =0, py = tworx2*y;

    void ellipse_points(Point , GLint, GLint);

    ellipse_points(p1, x, y);

	//region1
    p = round(ry2 - (rx2 - ry) + (2.5*rx2));
    while(px < py)
	{
		x++;
		px += twory2;
			if ( p < 0)
				p += ry2 + px;
			else{
				y--;
				py -= tworx2;
				p += ry2 + px - py;
			}
			ellipse_points(p1, x, y);
	}

	//region 2
	p = round(ry2*(x+0.5)*(x+0.5) + rx2*(y -1)*(y -1) - rx2*ry2);
	while(y>0)
	{
		 y--;
			py -= tworx2;
			if( p > 0)
				p += rx2 - py;
			else {
				x++;
				px += twory2;
				p += rx2 - py + px;
			}
		ellipse_points(p1, x, y);
	}
}

void ellipse_points(Point p1, int x, int y)
{
		glVertex2f(p1.x + x, p1.y + y);
		glVertex2f(p1.x - x, p1.y + y);
		glVertex2f(p1.x + x, p1.y - y);
		glVertex2f(p1.x - x, p1.y - y);
}

void init() {  //copied
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-700, 700, -600, 600);
}

void display(void) {
	Point p1 = {0, 0};
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		draw_ellipse(p1, 200,100);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)  //copied
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(700, 600);
	glutInitWindowPosition(150, 200);
	glutCreateWindow("Ellipse");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}