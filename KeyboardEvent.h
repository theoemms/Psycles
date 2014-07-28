#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H
#include <string.h>

using namespace std;

class KeyboardEvent
{
    public:
        string name;
        KeyboardEvent(string Name);
        virtual ~KeyboardEvent();
        virtual void keyPressed(unsigned char key, GLint x, GLint y) = 0;
        virtual void keyReleased(unsigned char key, GLint x, GLint y) = 0;
    protected:
    private:
};

class OnKeyPress : public KeyboardEvent
{
    public:
        Updatable* action;
        unsigned char key;
        bool keyAlreadyPressed;
        OnKeyPress(unsigned char Key, Updatable* Action, string name);
        virtual ~OnKeyPress();
        virtual void keyPressed(unsigned char Key, GLint x, GLint y);
        virtual void keyReleased(unsigned char Key, GLint x, GLint y);
    protected:
    private:
};

class OnKeyRelease : public KeyboardEvent
{
    public:
        Updatable* action;
        unsigned char key;
        bool keyAlreadyPressed;
        OnKeyRelease(unsigned char Key, Updatable* Action, string name);
        virtual ~OnKeyRelease();
        virtual void keyPressed(unsigned char Key, GLint x, GLint y);
        virtual void keyReleased(unsigned char Key, GLint x, GLint y);
    protected:
    private:
};

class OnKeyHold : public KeyboardEvent
{
    public:
        Updatable* action;
        unsigned char key;
        bool keyAlreadyPressed;
        OnKeyHold(unsigned char Key, Updatable* Action, string name);
        virtual ~OnKeyHold();
        virtual void keyPressed(unsigned char key, GLint x, GLint y);
        virtual void keyReleased(unsigned char key, GLint x, GLint y);
    protected:
    private:
};

#endif // KEYBOARDEVENT_H
