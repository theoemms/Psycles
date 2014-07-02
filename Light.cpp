#include "includes.h"

Light::Light(Vector3 Position, bool isDirectional, GLenum lightNumber)
{
    this->directional = isDirectional;
    this->position = Position;
    this->lightNum = lightNumber;
}

Light::~Light()
{
    //dtor
}

void Light::GLSetColour()
{
    glLightfv(this->lightNum, GL_AMBIENT, this->ambientColour);
    glLightfv(this->lightNum, GL_DIFFUSE, this->diffuseColour);
    glLightfv(this->lightNum, GL_SPECULAR, this->specularColour);
}

void Light::GLSetPosition()
{
    GLfloat* pos = this->GetGLPosition();
    glLightfv(this->lightNum, GL_POSITION, pos);
    free(pos);
}

GLfloat* Light::GetGLPosition() //The value this returns must be freed;
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
