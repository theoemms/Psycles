#include "includes.h"
#include<iostream>

#define MAX_DRAWABLES 32
#define MAX_LIGHTS 10
//The current state of this file is messy.
//This is because it is being used for testing out the basic functionality of the implemented classes.
//Once the Camera, Light and Drawable classes have been shown to work the Game class will
//exist to make this file much neater.

using namespace std;

//These are used to do a Hooke's law style physics simulation on the teapot (in idle());
Vector3 acceleration = Vector3(0, 0, 0);
Vector3 velocity = Vector3(9, 0, 0);

//The Drawable objects in the scene.
Teapot* teapot;
Triangle* triangle;

//The array of pointers to objects we  wish to be drawn.
Drawable* drawables[MAX_DRAWABLES];

//Out lights array
Light* lights[MAX_LIGHTS];
Light* light1, * light2;

Camera camera = Camera(Vector3(2, 0, 16), Vector3(0, 270, 0), false, 45, 3, 50); //The scene's camera

void draw() //This is called during every frame in order to first draw the scene to the
            //back buffer, then swap the front and back buffers.
{
    glClearColor(0,0,0,1); //Set the background colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //delete the previous frame
    glMatrixMode(GL_MODELVIEW); //Tell openGL we want to do transformations on the scene.
    glLoadIdentity(); //Create a new matrix to work from.

    camera.Translate(); //Translate to Scene coordinates

    for(int i = 0; i < MAX_LIGHTS; i++)
    {
        if(lights[i] != NULL) lights[i]->GLSetPosition();
    }
    for(int i = 0; i < MAX_DRAWABLES; i++) //Iterate over all the objects we wish to draw.
    {
        if (drawables[i] != NULL) drawables[i]->Draw(); //If they exist, draw them.
    }
    glutSwapBuffers(); //Present our back buffer to the screen and pull the previous frame into the back buffer
}

void idle() //This function runs when GLUT has nothing else to do. It's used for animation/physics.
{
    teapot->rotation.y += 5; //spin the teapot.
    if (teapot->rotation.y  >= 360.0f) //clamp the angle to 0 <= x < 360
        teapot->rotation.y  -= 360;

    acceleration = -teapot->position; //Hooke's law
    velocity += acceleration * 0.01;
    teapot->position += velocity * 0.01;

    triangle->rotation.y -= 7.5; //spin the triangle
    if (triangle->rotation.y  <= 0) //clamp as before
        triangle->rotation.y  += 360;

    camera.rotation.y += 2.5; //spin the camera
    if (camera.rotation.y  >= 360) //clamp as before
        camera.rotation.y  -= 360;

    glutPostRedisplay(); //Tell openGL the scene has been changed and therefore needs redrawing.
}

void init() //Get everything ready to go.
{
    for(int i = 0; i < MAX_DRAWABLES; i++) //Make sure that the Drawables are empty
    {
        drawables[i] = NULL;
    }
    for(int i = 0; i < MAX_LIGHTS; i++)
    {
        lights[i] = NULL;
    }
    teapot = new Teapot(); //Make a new teapot;
    triangle = new Triangle(); //Make a new triangle;
    teapot->position.z = 3; //Give the teapot a non-zero position in the z direction
    drawables[0] = teapot; //Set the teapot and triangle to be drawn every frame
    drawables[1] = triangle;

    light1 = new Light(Vector3(5, 1, 2), false, GL_LIGHT0);
    light1->SetAmbientColour(0, 0, 0.1f, 1);
    light1->SetDiffuseColour(0.4f, 0.35f, 0.3f, 1);
    light1->SetSpecularColour(0.3f, 0.3f, 0.3f, 1);

    light2 = new Light(Vector3(-5, 1, 2), false, GL_LIGHT1);
    light2->SetAmbientColour(0, 0, 0.1f, 1);
    light2->SetDiffuseColour(0.2f, 0.2f, 0.25f, 1);
    light1->SetSpecularColour(0, 0, 0, 1);

    lights[0] = light1;
    lights[1] = light2;

    glEnable(GL_LIGHTING);      //Let there be light
    glEnable(GL_DEPTH_TEST);    //Let there be depth testing!
                                //(OpenGL needs to work out wich parts of the scene aren't behind other objects)
    glEnable(GL_CULL_FACE);     //Don't draw the insides of objects
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void reshape(int width, int height) //This function is called when the window is created or changes shape.
{
    glViewport(0, 0, width, height); //Set the area of the window to draw in to be the whole window
    glMatrixMode(GL_PROJECTION); //Make sure the scene is projected onto the screen with the correst aspect ratio
    camera.SetProjection((float) width / height);
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

init(); //Set up the scene and enable openGL features

//Register idle(), display() and reshape()
glutIdleFunc(idle);
glutDisplayFunc(draw);
glutReshapeFunc(reshape);

glutMainLoop(); //Start the GLUT event loop

//pretty sure this is all unnecessary
delete teapot;
delete triangle;

for(int i = 0; i < MAX_DRAWABLES; i++) free(drawables[i]);

cout << "Error reporting ended.\n";
return 0;
}
