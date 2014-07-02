#include "includes.h"
#include<iostream>

#define MAX_DRAWABLES 32

//The current state of this file is messy.
//This is because it is being used for testing out the basic functionality of the implemented classes.
//Once the Camera, Light and Drawable classes have been shown to work the Game class will
//exist to make this file much neater.

using namespace std;

//The light's properties;
GLfloat light1Pos[4] = {5, 1, 2, 1};
GLfloat light2Pos[4] = {-5, -1, 2, 1};

GLfloat light1Diffuse[4] = {0.4f, 0.35f, 0.3f, 1};
GLfloat light1Specular[4] = {0.3f, 0.3f, 0.3f, 1};

GLfloat light2Diffuse[4] = {0.2f, 0.2f, 0.25f, 1};;
GLfloat light2Specular[4] = {0, 0, 0, 1};

//These are used to do a Hooke's law style physics simulation on the teapot (in idle());
Vector3 acceleration = Vector3(0, 0, 0);
Vector3 velocity = Vector3(9, 0, 0);

//The Drawable objects in the scene.
Teapot* teapot;
Triangle* triangle;

//The array of pointers to objects we  wish to be drawn.
Drawable* drawables[MAX_DRAWABLES];

void draw() //This is called during every frame in order to first draw the scene to the
            //back buffer, then swap the front and back buffers.
{
    glClearColor(0,0,0,1); //Set the background colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //delete the previous frame
    glMatrixMode(GL_MODELVIEW); //Tell openGL we want to do transformations on the scene.
    glLoadIdentity(); //Create a new matrix to work from.
    gluLookAt(2, 8, 16, 0, 0, 0, 0, 1, 0); //Transform from camera space to scene space
    glLightfv(GL_LIGHT0, GL_POSITION, light1Pos); //Set the light positions in scene space
    glLightfv(GL_LIGHT1, GL_POSITION, light2Pos);
    for(int i = 0; i < MAX_DRAWABLES; i++) //Iterate over all the objects we wish to draw.
    {
        if (drawables[i] != NULL) //If they exist, draw them.
            drawables[i]->Draw();
    }
    glutSwapBuffers(); //Present our back buffer to the screen and pull the previous frame into the back buffer
}

void idle() //This function runs when GLUT has nothing else to do. It's used for animation/physics.
{
    teapot->rotation.y += 5; //spin the teapot.
    if (teapot->rotation.y  >= 360.0f) //clamp the angle to 0 <= x < 360
        teapot->rotation.y  -= 360;

    acceleration = -teapot->position;
    velocity += acceleration * 0.01;
    teapot->position += velocity * 0.01;

    triangle->rotation.y -= 7.5; //spin the triangle
    if (triangle->rotation.y  <= 0) //clamp as before
        triangle->rotation.y  += 360;

    glutPostRedisplay(); //Tell openGL the scene has been changed and therefore needs redrawing.
}

void init() //Get everything ready to go.
{
    for(int i = 0; i < 32; i++) //Make sure that the Drawables are empty
    {
        drawables[i] = NULL;
    }
    teapot = new Teapot(); //Make a new teapot;
    triangle = new Triangle(); //Make a new triangle;
    teapot->position.z = 3; //Give the teapot a non-zero position in the z direction
    drawables[0] = teapot; //Set the teapot and triangle to be drawn every frame
    drawables[1] = triangle;
    glEnable(GL_LIGHTING); //Let there be light
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);    //Let there be depth testing!
                                //(OpenGL needs to work out wich parts of the scene aren't behind other objects)
    glEnable(GL_CULL_FACE); //Don't draw the insides of objects
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light1Diffuse); //Set the light colours
    glLightfv(GL_LIGHT0, GL_SPECULAR,light1Specular);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light2Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light2Specular);
}

void reshape(int width, int height) //This function is called when the window is created or changes shape.
{
    glViewport(0, 0, width, height); //Set the area of the window to draw in to be the whole window
    glMatrixMode(GL_PROJECTION); //Make sure the scene is projected onto the screen with the correst aspect ratio
    glLoadIdentity();
    gluPerspective(45, (float) width / height , 5, 30);
}


int main(int argc, char **argv)
{
cout << "Error reporting began. \n";
//Set up GLUT
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
glutInitWindowPosition(50,50);
glutInitWindowSize(500, 500);
glutCreateWindow("Psycles - Non euclidean horror.");

//Register idle(), display() and reshape()
glutIdleFunc(idle);
glutDisplayFunc(draw);
glutReshapeFunc(reshape);

init(); //Set up the scene and enable openGL features

glutMainLoop(); //Start the GLUT event loop

//pretty sure this is all unnecessary
delete teapot;
delete triangle;

for(int i = 0; i < MAX_DRAWABLES; i++) free(drawables[i]);

cout << "Error reporting ended.\n";
return 0;
}
