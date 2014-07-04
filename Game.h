#ifndef GAME_H
#define GAME_H

#define MAX_DRAWABLES 32
#define MAX_LIGHTS 16
#define MAX_CONSTRAINTS 64

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
        void RegisterDrawable(Drawable* drawable);
        void RegisterLight(Light* light);
        //void RegisterConstraint(Constraint* constraint);

        void UnregisterDrawable(Drawable* drawable);
        void UnregisterLight(Light* light);
        //void UnregisterConstraint(Constraint* constraint);

    protected:
    private:
        //The objects to be drawn, the lights to use in shading and any constraints to apply.
        Drawable* drawables[MAX_DRAWABLES];
        Light* lights[MAX_LIGHTS];
        //Constraint* constraints[MAX_CONSTRAINTS];

        //These are used to do a Hooke's law style physics simulation on the teapot (in idle());
        Vector3 acceleration;
        Vector3 velocity;

        //The Drawable objects in the scene.
        Teapot* teapot;
        Triangle* triangle;

        Light* light1, * light2;

        //This is to make OpenGL play with C++... Messy.

        static void drawCallback();

        static void reshapeCallback(GLint width, GLint height);

        static void idleCallback();
};

extern Game* game; //Global pointer to the game.

#endif // GAME_H
