#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

void generateColors();
double random(bool reset = false);
void drawPyramid(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d);
void dividePyramid(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int iterations);
void special(int key, int x, int y);
void display();
void doZoom();
void init();

GLfloat pyramid[4][3] = {{-1.0, -1.0, -1.0},
						 {1.0, -1.0, -1.0},
						 {0.0, -1.0, 0.732},
						 {0.0, 1.0, -0.134}};

double colors[1000] = {0};

double angle = 0;
int iterations = 4;
double zoom = 0;
int shading = GL_SMOOTH;

void generateColors()
{
	for (int i = 0; i < 1000; i++)
	{
		colors[i] = rand() / (double)RAND_MAX;
	}
}

double random(bool reset)
{
	static int curr = 0;
	if (reset)
	{
		curr = 0;
		return 0.0;
	}
	else
	{
		if (curr >= 1000)
			curr = 0;
		return colors[curr++];
	}
}

void drawPyramid(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(shading);

	glBegin(GL_TRIANGLES);
	glColor3f(rand(), rand(), rand());
	glVertex3fv(a);
	glColor3f(rand(), rand(), rand());
	glVertex3fv(b);
	glColor3f(rand(), rand(), rand());
	glVertex3fv(c);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(rand(), rand(), rand());
	glVertex3fv(a);
	glColor3f(rand(), rand(), rand());
	glVertex3fv(b);
	glColor3f(rand(), rand(), rand());
	;
	glVertex3fv(d);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(rand(), rand(), rand());
	glVertex3fv(a);
	glColor3f(rand(), rand(), rand());
	glVertex3fv(c);
	glColor3f(rand(), rand(), rand());
	glVertex3fv(d);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(rand(), rand(), rand());
	glVertex3fv(b);
	glColor3f(rand(), rand(), rand());
	glVertex3fv(c);
	glColor3f(rand(), rand(), rand());
	glVertex3fv(d);
	glEnd();
}

void dividePyramid(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int iterations)
{
	GLfloat v[6][3];
	int j;
	if (iterations > 0)
	{
		for (j = 0; j < 3; j++)
		{
			v[0][j] = (a[j] + b[j]) / 2;
		}
		for (j = 0; j < 3; j++)
		{
			v[1][j] = (a[j] + c[j]) / 2;
		}
		for (j = 0; j < 3; j++)
		{
			v[2][j] = (b[j] + c[j]) / 2;
		}
		for (j = 0; j < 3; j++)
		{
			v[3][j] = (a[j] + d[j]) / 2;
		}
		for (j = 0; j < 3; j++)
		{
			v[4][j] = (b[j] + d[j]) / 2;
		}
		for (j = 0; j < 3; j++)
		{
			v[5][j] = (c[j] + d[j]) / 2;
		}

		dividePyramid(a, v[0], v[1], v[3], iterations - 1);
		dividePyramid(v[0], b, v[2], v[4], iterations - 1);
		dividePyramid(v[1], v[2], c, v[5], iterations - 1);
		dividePyramid(v[3], v[4], v[5], d, iterations - 1);
	}
	else
	{
		drawPyramid(a, b, c, d);
	}
}

void special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		if (zoom - 0.1 > -1)
			zoom -= 0.05;
		doZoom();
		break;
	case GLUT_KEY_DOWN:
		zoom += 0.05;
		doZoom();
		break;
	case GLUT_KEY_RIGHT:
		angle += 1;
		if (angle > 360)
		{
			angle = 0;
		}
		break;
	case GLUT_KEY_LEFT:
		angle -= 1;
		if (angle < 0)
		{
			angle = 360;
		}
		break;
	}
}

void doZoom()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 - zoom, 1.0 + zoom, -1.0 - zoom, 1.0 + zoom, -20.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	display();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(angle, 0, 1, 0);

	random(true);
	dividePyramid(pyramid[0], pyramid[1], pyramid[2], pyramid[3], iterations);

	glPopMatrix();
	glFlush();

	glutPostRedisplay();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -20.0, 20.0);
	glEnable(GL_DEPTH_TEST);
}

void glutInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-620.0, 620.0, -340.0, 340.0);
}
int main(int argc, char **argv)
{
	srand(time(NULL));

	generateColors();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Sierpinski Triangle");
	glutPositionWindow(100, 100);
	glutSpecialFunc(special);
	glutDisplayFunc(display);
	zoom+=1;
	doZoom();
	glutMainLoop();
}
