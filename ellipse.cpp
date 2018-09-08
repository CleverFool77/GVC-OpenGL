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

void draw_ellipse(Point p, GLint rx , GLint ry)
{
    GLint rx2 = rx*rx;
    GLint ry2 = ry*ry;
    GLint tworx2 = 2*rx2;
    GLint twory2 = 2*ry2;
    GLint p,x = 0,y = ry;
    GLint px =0, py = tworx2*y;

    void ellipse_points(GLint, GLint , GLint, GLint);

    ellipse_points(p.x, p.y, x, y);

    p = round(ry2(rx2 - ry)+(2.5*rx2));
    

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
	glutCreateWindow("Ellipse");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}