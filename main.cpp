#include "includes.h"
#include <sstream>

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
    delete game, light1, light2, triangle, teapot, teapot2;
}

int main(int argc, char **argv) //Nice and general, all implementation details abstracted out.
{
    atexit(cleanup);
    game = new Game();
    game->Initiallise(argc, argv);
    
    light1 = new Light(Vector3(1, 20, 2), false, GL_LIGHT0, "Sun");
    light1->SetAmbientColour(0, 0, 0.1f, 1);
    light1->SetDiffuseColour(0.4f, 0.35f, 0.3f, 1);
    light1->SetSpecularColour(0.3f, 0.3f, 0.3f, 1);

    light2 = new Light(Vector3(-5, 1, 2), false, GL_LIGHT1, "Sky Reflection");
    light2->SetAmbientColour(0, 0, 0.1f, 1);
    light2->SetDiffuseColour(0.2f, 0.2f, 0.25f, 1);
    light2->SetSpecularColour(0, 0, 0, 1);

    teapot = new Teapot("Teapot 1");
    teapot2 = new Teapot("Teapot 2");
    triangle = new Triangle("Triangle");
    
    for(int z = 0; z < 4; z++)
        for(int x = 0; x < 4; x++)
        {
            std:ostringstream oss;
            oss << "Plane subdivision (" << x << ", " << z << ")";
            planes[4*z + x] = new Plane(oss.str());
            planes[4*z + x]->position = Vector3((x - 1.5f) * 2.5f, -0.8f, (z - 1.5f) * 2.5f);
            planes[4*z + x]->scale = 1.25f;
        }
     
    triangle->position.y = 2;

    teapot2->position = Vector3(2, 2, 2);

    teapotStack = new CompoundDrawable(2, "Teapot Stack");
    teapotStack->children[0] = teapot;
    teapotStack->children[1] = teapot2;

    ScaleAnimation* rotateTeapots = new ScaleAnimation(&teapotStack->rotation.y, 25, "Rotate Teapots");
    
    game->RegisterDrawable(teapotStack);
    game->RegisterDrawable(triangle);
    for(int i = 0; i < 16; i++)
        game->RegisterDrawable(planes[i]);
    game->RegisterUpdatable(rotateTeapots);
    game->RegisterLight(light1);
    game->RegisterLight(light2);
    game->Run();

    return 0;
}
