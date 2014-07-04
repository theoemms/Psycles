#ifndef GAME_H
#define GAME_H

#define MAX_DRAWABLES 32
#define MAX_LIGHTS 16
#define MAX_UPDATABLES 64

#include<string>

using namespace std;

class Game
{
    public:
        Camera* camera; //The scene's camera

        Game();
        virtual ~Game();

        void Initiallise(int argc, char **argv); //Set up GLUT, register callbacks, initiallise the drawables, lights and constraints.
        void Run();

        void Update(); //GLUTs idle callback
        void Draw(); //GLUTs display callback
        void Reshape(GLint width, GLint height); //GLUTs reshape callback

        //Error reporting functions.
        static void Report(const string message);
        static void Warn(const string warning);
        static void Fatal(const string error);

        //Register and unregister functions;
        uint RegisterDrawable(Drawable* drawable, string name);
        uint RegisterLight(Light* light, string name);
        uint RegisterUpdatable(Updatable* updatable, string name);

        void UnregisterDrawable(Drawable* drawable);
        void UnregisterLight(Light* light);
        void UnregisterUpdatable(Updatable* updatable);

    protected:
    private:
        //The objects to be drawn, the lights to use in shading and any constraints to apply.
        Drawable* drawables[MAX_DRAWABLES];
        Light* lights[MAX_LIGHTS];
        Updatable* updatables[MAX_UPDATABLES];

        //This is to make OpenGL play with C++... Messy. Essentially maps Update, Draw etc. to these static functions
        //(Means only one instance of Game can exist)
        static void drawCallback();
        static void reshapeCallback(GLint width, GLint height);
        static void idleCallback();
};

extern Game* game; //Global pointer to the game.

#endif // GAME_H
