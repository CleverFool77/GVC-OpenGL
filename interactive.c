#include <GL/glut.h>
#include <math.h>
#include <GL/gl.h>
#include <stdio.h>

struct Point
{
    GLint x;
    GLint y;
};

int rotate_option = 0; // 0 clockwise and 1 anti clockwise
int scale_option = 0;  // 0 smaller and 1 scale bigger

Point scaling(Point p2, GLfloat nooftimes)
{
    Point p3;
    p3.x = p2.x * nooftimes;
    p3.y = p2.y * nooftimes;

    return p3;
}

Point rotating(Point p, GLfloat angle)
{
    Point p2;
    p2.x = 0 + (p.x - 0) * cos(angle) - (p.y - 0) * sin(angle);
    p2.y = 0 + (p.x - 0) * sin(angle) + (p.y - 0) * cos(angle);

    return p2;
}

void draw_line(Point a, Point b)

{
    GLfloat dx = b.x - a.x;
    GLfloat dy = b.y - a.y;

    GLfloat x1 = a.x;
    GLfloat y1 = a.y;

    GLfloat steps = 0;

    if (abs(dx) > abs(dy))
    {
        steps = abs(dx);
    }

    else
    {
        steps = abs(dy);
    }

    GLfloat xInc = dx / steps;
    GLfloat yInc = dy / steps;

    for (float i = 1.00; i <= steps; i++)
    {
        glVertex2f(x1, y1);
        x1 += xInc;
        y1 += yInc;
    }
}

void draw_square(Point p1, GLint length)
{
    Point p2;
    p2.x = p1.x + length;
    p2.y = p1.y;

    draw_line(p1, p2);

    Point p3;
    p3.x = p2.x;
    p3.y = p2.y + length;

    draw_line(p2, p3);

    Point p4;
    p4.x = p1.x;
    p4.y = p1.y + length;

    draw_line(p4, p3);

    draw_line(p1, p4);
}

void key_handler(unsigned char key, int x, int y)
{
    if (key == 'r')
    {
        printf("%d rotate\n", rotate_option);
        if (rotate_option == 1)
        {
            glRotatef(10,0.0,0.0,1.0);
            glutPostRedisplay();
        }
        if (rotate_option == 0)
        {
            glRotatef(10, 0.0, 0.0, -1.0);
            glutPostRedisplay();
        }
    }
    if (key == 's')
    {
        if (scale_option == 1)
        {
            glScalef(1.3, 1.3, 1);
            glutPostRedisplay();
        }
        if (scale_option == 0)
        {
            glScalef(0.3, 0.3, 1);
            glutPostRedisplay();
        }
    }
}

void mouse_handler(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
        {
            printf("%d %d\n", x, y);
            if (x >= 0 && x <= 50 && y >= 0 && y <= 50)
            {
                rotate_option = 1;
                scale_option = 1;
            }
            if (x <= 700 && x >= 650 && y >= 0 && y <= 50)
            {
                rotate_option = 0;
                scale_option = 0;
            }
        }
    }
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 700, 0, 600);
}

void display()
{
    Point p1 = {100, 100};
    Point p2 = {500, 100};
    GLint length = 300;
    GLint length1 = 20;
    Point t1 = {500, 200};
    Point t2 = {450, 100};
    Point t3 = {550, 100};
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    draw_square(p1, length);
    glEnd();

    glBegin(GL_POINTS);
    draw_line(t1, t2);
    draw_line(t2, t3);
    draw_line(t1, t3);
    glEnd();

    glutMouseFunc(mouse_handler);
    glutKeyboardFunc(key_handler);

    glFlush();
}

int main(int argc, char **argv) //copied
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(150, 200);
    glutCreateWindow("Cuboid and triangle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
