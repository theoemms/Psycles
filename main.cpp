#include "includes.h"

using namespace std;

Game* game;

//The Drawable objects in the scene.
Teapot* teapot;
Teapot* teapot2;
Triangle* triangle;
Plane* plane;

Light* light1, * light2;

ScaleAnimation* scaleTeapot;

void cleanup()
{
    delete game, light1, light2, triangle, teapot, plane;
}

void mouse(GLint button, GLint state, GLint x, GLint y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        game->RegisterUpdatable(scaleTeapot, "teapot scale");
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        game->UnregisterUpdatable(scaleTeapot);
    }
}

int main(int argc, char **argv) //Nice and general, all implementation details abstracted out.
{
    atexit(cleanup);
    game = new Game();
    game->Initiallise(argc, argv);

    glutMouseFunc(mouse); //*cough*

    Game::Report("");

    light1 = new Light(Vector3(1, 20, 2), false, GL_LIGHT0);
    light1->SetAmbientColour(0, 0, 0.1f, 1);
    light1->SetDiffuseColour(0.4f, 0.35f, 0.3f, 1);
    light1->SetSpecularColour(0.3f, 0.3f, 0.3f, 1);

    light2 = new Light(Vector3(-5, 1, 2), false, GL_LIGHT1);
    light2->SetAmbientColour(0, 0, 0.1f, 1);
    light2->SetDiffuseColour(0.2f, 0.2f, 0.25f, 1);
    light2->SetSpecularColour(0, 0, 0, 1);

    teapot = new Teapot();
    teapot2 = new Teapot();
    triangle = new Triangle();
    plane = new Plane();

    plane->position.y = -1;
    plane->scale = 10;

    triangle->position.y = 2;

    teapot2->position = Vector3(2, 2, 2);

    scaleTeapot = new ScaleAnimation(&teapot2->scale, 0.5);

    game->RegisterDrawable(teapot2, "another teapot");
    game->RegisterDrawable(teapot, "Teapot");
    game->RegisterDrawable(triangle, "Triangle");
    game->RegisterDrawable(plane, "Plane");
    game->RegisterLight(light1, "Sun");
    game->RegisterLight(light2, "Sky Reflection");
    game->RegisterUpdatable(scaleTeapot, "teapot scale");

    game->Run();

    return 0;
}
