#include "includes.h"
#include<iostream>

using namespace std;

GLfloat light1Pos[4] = {5, 1, 2, 1};
GLfloat light2Pos[4] = {-5, -1, 2, 1};

GLfloat light1Diffuse[4] = {0.4f, 0.35f, 0.3f, 1};
GLfloat light1Specular[4] = {0.3f, 0.3f, 0.3f, 1};

GLfloat light2Diffuse[4] = {0.2f, 0.2f, 0.25f, 1};;
GLfloat light2Specular[4] = {0, 0, 0, 1};

float acceleration[3] = {0, 0, 0};
float velocity[3] = {9, 0, 0};
Teapot* teapot;
Triangle* triangle;
Drawable* drawables[32];

void draw()
{
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2, 8, 16, 0, 0, 0, 0, 1, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, light1Pos);
    glLightfv(GL_LIGHT1, GL_POSITION, light2Pos);
    for(int i = 0; i < 32; i++)
    {
        if (drawables[i] != NULL)
            drawables[i]->Draw();
    }
    glutSwapBuffers();
}

void idle()
{
    teapot->rotation[1] += 5;
    if (teapot->rotation[1]  >= 360.0f)
        teapot->rotation[1]  -= 360;
    triangle->rotation[1] -= 7.5;
    if (triangle->rotation[1]  <= 0)
        triangle->rotation[1]  += 360;
    for (int i = 0; i < 3; i++)
    {
        acceleration[i] = -teapot->position[i];
        velocity[i] += acceleration[i] * 0.01;
        teapot->position[i] += velocity[i] * 0.01;
    }
    glutPostRedisplay();
}

void init()
{
    for(int i = 0; i < 32; i++)
    {
        drawables[i] = NULL;
    }
    teapot = new Teapot();
    triangle = new Triangle();
    teapot->position[2] = 3;
    drawables[0] = teapot;
    drawables[1] = triangle;
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light1Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR,light1Specular);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light2Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light2Specular);
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float) width / height , 5, 30);
}

//Main program
int main(int argc, char **argv)
{
cout << "Error reporting began. \n";
glutInit(&argc, argv);
//Simple buffer
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
glutInitWindowPosition(50,50);
glutInitWindowSize(500, 500);
glutCreateWindow("Psycles - Non euclidean horror.");
glutIdleFunc(idle);
glutDisplayFunc(draw);
glutReshapeFunc(reshape);
init();
glutMainLoop();
return 0;
}
