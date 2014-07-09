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
    for(int i = 0; i < MAX_LIGHTS; i++) //Do the same for lights
    {
        this->lights[i] = NULL;
    }
    for(int i = 0; i < MAX_UPDATABLES; i++) //Do the same for updatables
    {
        this->updatables[i] = NULL;
    }
    for(int i = 0; i < MAX_KEYEVENTS; i++) //Do the same for keyboard events
    {
        this->keyboardEvents[i] = NULL;
    }
}

Game::~Game()
{
    delete this->camera;
}

void Game::Initiallise(int argc, char **argv)
{
    //Set up GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowPosition(50,50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Psycles - Non euclidean horror.");

    this->camera = new Camera(Vector3(2, 0, 16), Vector3(0, 0, 0), true, 45, 3, 50);

    glEnable(GL_LIGHTING);      //Let there be light
    glEnable(GL_DEPTH_TEST);    //Let there be depth testing!
                                //(OpenGL needs to work out wich parts of the scene aren't behind other objects)
    glEnable(GL_CULL_FACE);     //Don't draw the insides of objects
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glutDisplayFunc(Game::drawCallback);
    glutIdleFunc(Game::idleCallback);
    glutReshapeFunc(Game::reshapeCallback);
    glutKeyboardFunc(Game::keyDownCallback);
    glutKeyboardUpFunc(Game::keyUpCallback);
}

void Game::Run()
{
    glutMainLoop(); //Start the GLUT event loop
}

void Game::Update()
{
    glutPostRedisplay(); //Tell openGL the scene has been changed and therefore needs redrawing.

    float deltaT = Globals::timeStep;

    for(int i = 0; i < MAX_UPDATABLES; i++)
    {
        if(updatables[i] != NULL)
            updatables[i]->Update(deltaT);
    }
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

void Game::KeyUp(char Key, GLint x, GLint y)
{
    for(int i = 0; i < MAX_KEYEVENTS; i++)
    {
        if(this->keyboardEvents[i] != NULL) this->keyboardEvents[i]->keyReleased(Key, x, y);
    }
}
void Game::KeyDown(char Key, GLint x, GLint y)
{
    for(int i = 0; i < MAX_KEYEVENTS; i++)
    {
        if(this->keyboardEvents[i] != NULL) this->keyboardEvents[i]->keyPressed(Key, x, y);
    }
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

uint Game::RegisterDrawable(Drawable* drawable, string name)
{
    bool isAlreadyRegistered = false;
    for(int i = 0; i < MAX_DRAWABLES; i++) //Scan through the list to check if the drawable is in there.
    {
        isAlreadyRegistered = isAlreadyRegistered | (drawable == this->drawables[i]);
    }
    if(isAlreadyRegistered)
    {
        Game::Warn("Drawable already registered: " + name);
    }
    else
    {
        bool success = false;
        uint index;
        for(int i = 0; i < MAX_DRAWABLES; i++) //Scan through the list to find a space
        {
            if(this->drawables[i] == NULL) //if you find one
            {
                index = i; //remember where you put it
                this->drawables[i] = drawable; //put it there
                success = true; //remember that you put it
                break; //stop looking
            }
        }
        if(!success) Game::Fatal("Drawable memory full. Could not add " + name + "."); //if there was no space, panic!
        else return index; //give back the index so we can deassign quickly
    }
}

uint Game::RegisterLight(Light* light, string name)
{
    glEnable(light->lightNum);
    bool isAlreadyRegistered = false;
    for(int i = 0; i < MAX_LIGHTS; i++) //Scan through the list to check if the drawable is in there.
    {
        isAlreadyRegistered = isAlreadyRegistered | (light == this->lights[i]);
    }
    if(isAlreadyRegistered)
    {
        Game::Warn("Light already registered: " + name);
    }
    else
    {
        bool success = false;
        uint index;
        for(int i = 0; i < MAX_LIGHTS; i++) //Scan through the list to check if the drawable is in there.
        {
            if(this->lights[i] == NULL)
            {
                index == i;
                this->lights[i] = light;
                success = true;
                break;
            }
        }
        if(!success) Game::Fatal("Too many lights assigned!");
        else return index;
    }
}

uint Game::RegisterUpdatable(Updatable* updatable)
{
    bool isAlreadyRegistered = false;
    for(int i = 0; i < MAX_UPDATABLES; i++) //Scan through the list to check if the drawable is in there.
    {
        isAlreadyRegistered = isAlreadyRegistered | (updatable == this->updatables[i]);
    }
    if(isAlreadyRegistered)
    {
        Game::Warn("Drawable already registered: " + updatable->name);
    }
    else
    {
        bool success = false;
        uint index;
        for(int i = 0; i < MAX_UPDATABLES; i++) //Scan through the list to find a space
        {
            if(this->updatables[i] == NULL) //if you find one
            {
                index = i; //remember where you put it
                this->updatables[i] = updatable; //put it there
                success = true; //remember that you put it
                break; //stop looking
            }
        }
        if(!success) Game::Fatal("Updatable memory full. Could not add " + updatable->name + "."); //if there was no space, panic!
        else return index; //give back the index so we can deassign
    }
}

uint Game::RegisterKeyboardEvent(KeyboardEvent* event, string name)
{
    bool isAlreadyRegistered = false;
    for(int i = 0; i < MAX_KEYEVENTS; i++) //Scan through the list to check if the drawable is in there.
    {
        isAlreadyRegistered = isAlreadyRegistered | (event == this->keyboardEvents[i]);
    }
    if(isAlreadyRegistered)
    {
        Game::Warn("Keyboard event already registered: " + name);
    }
    else
    {
        bool success = false;
        uint index;
        for(int i = 0; i < MAX_KEYEVENTS; i++) //Scan through the list to find a space
        {
            if(this->keyboardEvents[i] == NULL) //if you find one
            {
                index = i; //remember where you put it
                this->keyboardEvents[i] = event; //put it there
                success = true; //remember that you put it
                break; //stop looking
            }
        }
        if(!success) Game::Fatal("Keyboard event memory full. Could not add " + name + "."); //if there was no space, panic!
        else return index; //give back the index so we can deassign
    }
}

void Game::UnregisterDrawable(Drawable* drawable)
{
    bool success = false;
    for (int i = 0; i < MAX_DRAWABLES; i++)
    {
        if(drawable == this->drawables[i])
        {
            this->drawables[i] = NULL;
            success = true;
            //note, we don't break this way if any duplicate additions happen they are removed.
        }
    }
    if (!success) Game::Warn("Tried to remove non existent drawable!");
}

void Game::UnregisterLight(Light* light)
{
    glDisable(light->lightNum);
    bool success = false;
    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        if(light == this->lights[i])
        {
            this->lights[i] = NULL;
            success = true;
            //note, we don't break this way if any duplicate additions happen they are removed.
        }
    }
    if (!success) Game::Warn("Tried to remove non existent light!");
}

void Game::UnregisterUpdatable(Updatable* updatable)
{
    bool success = false;
    for (int i = 0; i < MAX_UPDATABLES; i++)
    {
        if(updatable == this->updatables[i])
        {
            this->updatables[i] = NULL;
            success = true;
            //note, we don't break this way if any duplicate additions happen they are removed.
        }
    }
    if (!success) Game::Warn("Tried to remove non existent updatable: " + updatable->name);
}

void Game::UnregisterKeyboardEvent(KeyboardEvent* event)
{
    bool success = false;
    for (int i = 0; i < MAX_KEYEVENTS; i++)
    {
        if(event == this->keyboardEvents[i])
        {
            this->keyboardEvents[i] = NULL;
            success = true;
            //note, we don't break this way if any duplicate additions happen they are removed.
        }
    }
    if (!success) Game::Warn("Tried to remove non existent updatable!");
}

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

void Game::keyUpCallback(unsigned char Key, GLint x, GLint y)
{
    game->KeyUp(Key, x, y);
}

void Game::keyDownCallback(unsigned char Key, GLint x, GLint y)
{
    game->KeyDown(Key, x, y);
}
