#include "includes.h"
#include<iostream>

#include<string>

using namespace std;

Game::Game()
{
    for(int i = 0; i < MAX_DRAWABLES; i++) //Make sure that the Drawables are empty
    {
        this->drawables[i] = NULL;
    }
    for(int i = 0; i < MAX_LIGHTS; i++)
    {
        this->lights[i] = NULL;
    }

    this->acceleration = Vector3(0, 0, 0);
    this->velocity = Vector3(9, 0, 0);
}

Game::~Game()
{
    //dtor
}

void Game::Initiallise(int argc, char **argv)
{
    //Set up GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowPosition(50,50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Psycles - Non euclidean horror.");

    this->light1 = new Light(Vector3(5, 1, 2), false, GL_LIGHT0);
    this->light1->SetAmbientColour(0, 0, 0.1f, 1);
    this->light1->SetDiffuseColour(0.4f, 0.35f, 0.3f, 1);
    this->light1->SetSpecularColour(0.3f, 0.3f, 0.3f, 1);

    this->light2 = new Light(Vector3(-5, 1, 2), false, GL_LIGHT1);
    this->light2->SetAmbientColour(0, 0, 0.1f, 1);
    this->light2->SetDiffuseColour(0.2f, 0.2f, 0.25f, 1);
    this->light2->SetSpecularColour(0, 0, 0, 1);

    this->lights[0] = light1;
    this->lights[1] = light2;

    this->camera = new Camera(Vector3(2, 4, 16), Vector3(0, 0, 0), true, 45, 3, 50);

    this->teapot = new Teapot(); //Make a new teapot;
    this->triangle = new Triangle(); //Make a new triangle;
    this->teapot->position.z = 3; //Give the teapot a non-zero position in the z direction
    this->drawables[0] = teapot; //Set the teapot and triangle to be drawn every frame
    this->drawables[1] = triangle;

    glEnable(GL_LIGHTING);      //Let there be light
    glEnable(GL_DEPTH_TEST);    //Let there be depth testing!
                                //(OpenGL needs to work out wich parts of the scene aren't behind other objects)
    glEnable(GL_CULL_FACE);     //Don't draw the insides of objects
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glutDisplayFunc(Game::drawCallback);
    glutIdleFunc(Game::idleCallback);
    glutReshapeFunc(Game::reshapeCallback);
}

void Game::Run()
{
    glutMainLoop(); //Start the GLUT event loop
}

void Game::Update()
{
    this->teapot->rotation.y += 5; //spin the teapot.
    if (this->teapot->rotation.y  >= 360.0f) //clamp the angle to 0 <= x < 360
        this->teapot->rotation.y  -= 360;

    this->acceleration = -this->teapot->position; //Hooke's law
    this->velocity += this->acceleration * 0.01;
    this->teapot->position += this->velocity * 0.01;

    this->triangle->rotation.y -= 7.5; //spin the triangle
    if (this->triangle->rotation.y  <= 0) //clamp as before
        this->triangle->rotation.y  += 360;

    glutPostRedisplay(); //Tell openGL the scene has been changed and therefore needs redrawing.
}

void Game::Draw()
{
    glClearColor(0,0,0,1); //Set the background colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //delete the previous frame
    glMatrixMode(GL_MODELVIEW); //Tell openGL we want to do transformations on the scene.
    glLoadIdentity(); //Create a new matrix to work from.

    this->camera->Translate(); //Translate to Scene coordinates

    for(int i = 0; i < MAX_LIGHTS; i++) //Set the lights positions.
    {
        if(this->lights[i] != NULL) this->lights[i]->GLSetPosition();
    }

    for(int i = 0; i < MAX_DRAWABLES; i++) //Iterate over all the objects we wish to draw.
    {
        if (this->drawables[i] != NULL)//If they exist, draw them.
        {
            glPushMatrix(); //Do not allow an objects draw call to transform anything other than itself.
            this->drawables[i]->Draw();
            glPopMatrix();
        }
    }
    glutSwapBuffers(); //Present our back buffer to the screen and pull the previous frame into the back buffer
}

void Game::Reshape(GLint width, GLint height)
{
    glViewport(0, 0, width, height); //Set the area of the window to draw in to be the whole window
    glMatrixMode(GL_PROJECTION); //Make sure the scene is projected onto the screen with the correst aspect ratio
    this->camera->SetProjection((float) width / height);
}

void Game::Report(const string message)
{
    cout << message << '\n';
}

void Game::Warn(const string warning)
{
    Game::Report("Warning: " + warning);
}

void Game::Fatal(const string error)
{
    Game::Report("Fatal: " + error);
    exit(1);
}

void Game::RegisterDrawable(Drawable* drawable)
{

}

void Game::RegisterLight(Light* light)
{

}

//void RegisterConstraint(Constraint* constraint){}

void Game::UnregisterDrawable(Drawable* drawable)
{

}

void Game::UnregisterLight(Light* light)
{

}

//void UnregisterConstraint(Constraint* constraint){}

void Game::drawCallback()
{
    game->Draw();
}

void Game::reshapeCallback(GLint width, GLint height)
{
    game->Reshape(width, height);
}

void Game::idleCallback()
{
    game->Update();
}


