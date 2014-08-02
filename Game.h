#ifndef GAME_H
#define GAME_H

#define MAX_DRAWABLES 512
#define MAX_LIGHTS 16
#define MAX_UPDATABLES 2048
#define MAX_KEYEVENTS 512

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

        //Keyboard input functions
        void KeyDown(char Key, GLint x, GLint y);
        void KeyUp(char Key, GLint x, GLint y);

        //Error reporting functions.
        static void Report(const string message);
        static void Warn(const string warning);
        static void Fatal(const string error);

        //Register and unregister functions;
        uint RegisterDrawable(Drawable* drawable);
        uint RegisterLight(Light* light);
        uint RegisterUpdatable(Updatable* updatable);
        uint RegisterKeyboardEvent(KeyboardEvent* event);

        void UnregisterDrawable(Drawable* drawable);
        void UnregisterLight(Light* light);
        void UnregisterUpdatable(Updatable* updatable);
        void UnregisterKeyboardEvent(KeyboardEvent* event);
    protected:
    private:
        //The objects to be drawn, the lights to use in shading and any constraints to apply.
        Drawable** drawables;
        Light** lights;
        Updatable** updatables;
        KeyboardEvent** keyboardEvents;

        //This is to make OpenGL play with C++... Messy. Essentially maps Update, Draw etc. to these static functions
        //(Means only one instance of Game can exist)
        static void drawCallback();
        static void reshapeCallback(GLint width, GLint height);
        static void idleCallback();
        static void keyUpCallback(unsigned char Key, GLint x, GLint y);
        static void keyDownCallback(unsigned char Key, GLint x, GLint y);

};

extern Game* game; //Global pointer to the game.

#endif // GAME_H
