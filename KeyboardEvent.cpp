#include "includes.h"

KeyboardEvent::KeyboardEvent(string Name)
{
    this->name = Name;
}

KeyboardEvent::~KeyboardEvent()
{
    //dtor
}

OnKeyPress::OnKeyPress(unsigned char Key, Updatable* Action, string name) : KeyboardEvent(name)
{
    this->key = Key;
    this->action = Action;
    this->keyAlreadyPressed = false;
}

OnKeyPress::~OnKeyPress(){}

void OnKeyPress::keyPressed(unsigned char Key, GLint x, GLint y)
{
    if (this->key == Key && !this->keyAlreadyPressed)
    {
        this->keyAlreadyPressed = true;
        game->RegisterUpdatable(this->action);
    }
}

void OnKeyPress::keyReleased(unsigned char Key, GLint x, GLint y)
{
    if (this->key == Key && this->keyAlreadyPressed)
    {
        this->keyAlreadyPressed = false;
    }
}

OnKeyRelease::OnKeyRelease(unsigned char Key, Updatable* Action, string name) : KeyboardEvent(name)
{
    this->key = Key;
    this->action = Action;
    this->keyAlreadyPressed = false;
}

OnKeyRelease::~OnKeyRelease(){}

void OnKeyRelease::keyPressed(unsigned char Key, GLint x, GLint y){}

void OnKeyRelease::keyReleased(unsigned char Key, GLint x, GLint y)
{
    if (this->key == Key)
    {
        game->RegisterUpdatable(this->action);
    }
}

OnKeyHold::OnKeyHold(unsigned char Key, Updatable* Action, string name) : KeyboardEvent(name)
{
    this->key = Key;
    this->action = Action;
    this->keyAlreadyPressed = false;
}

OnKeyHold::~OnKeyHold(){}

void OnKeyHold::keyPressed(unsigned char Key, GLint x, GLint y)
{
    if (this->key == Key && !this->keyAlreadyPressed)
    {
        this->keyAlreadyPressed = true;
        game->RegisterUpdatable(this->action);
    }
}

void OnKeyHold::keyReleased(unsigned char Key, GLint x, GLint y)
{
    if (this->key == Key && this->keyAlreadyPressed)
    {
        this->keyAlreadyPressed = false;
        game->UnregisterUpdatable(action);
    }
}
