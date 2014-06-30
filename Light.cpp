#include "includes.h"

Light::Light(Vector3 Position, bool isDirectional)
{
    this->directional = isDirectional;
    this->position = Position;
}

Light::~Light()
{
    //dtor
}

GLfloat* Light::GetGLPosition()
{
    if(this->directional)
    {
        return this->position.ToGLFloat4(0);
    }
    else
    {
        return this->position.ToGLFloat4(1);
    }
}
