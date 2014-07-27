#include "includes.h"

using namespace std;

Game* game;

//The Drawable objects in the scene.
Teapot* teapot;
Teapot* teapot2;
Triangle* triangle;
Plane* planes[16];

CompoundDrawable* teapotStack;

Light* light1, * light2;

void cleanup()
{
    delete game, light1, light2, triangle, teapot;
}

int main(int argc, char **argv) //Nice and general, all implementation details abstracted out.
{
    atexit(cleanup);
    game = new Game();
    game->Initiallise(argc, argv);

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
    
    for(int z = 0; z < 4; z++)
        for(int x = 0; x < 4; x++)
        {
            planes[4*z + x] = new Plane();
            planes[4*z + x]->position = Vector3((x - 2) * 2.5f, -0.8f, (z - 2) * 2.5f);
            planes[4*z + x]->scale = 2.5f;
        }
     
    triangle->position.y = 2;

    teapot2->position = Vector3(2, 2, 2);

    teapotStack = new CompoundDrawable(2);
    teapotStack->children[0] = teapot;
    teapotStack->children[1] = teapot2;

    ScaleAnimation* growTeapots = new ScaleAnimation(&teapotStack->rotation.y, 5, "GrowTeapots");
    
    Vector3Report* reportCameraPosition = new Vector3Report(&game->camera->position, "Camera Position Reporter.");
    OnKeyPress* reportCameraPositionEvent = new OnKeyPress('p', reportCameraPosition);
    
    game->RegisterDrawable(teapotStack, "teapotStack");
    game->RegisterDrawable(triangle, "Triangle");
    for(int i = 0; i < 16; i++)
        game->RegisterDrawable(planes[i], "Plane");
    game->RegisterUpdatable(growTeapots);
    game->RegisterLight(light1, "Sun");
    game->RegisterLight(light2, "Sky Reflection");
    game->RegisterKeyboardEvent(reportCameraPositionEvent, "Report Camera Position");
    game->Run();

    return 0;
}
