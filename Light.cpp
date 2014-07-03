#include "includes.h"

Light::Light(Vector3 Position, bool isDirectional, GLenum lightNumber)
{
    this->directional = isDirectional;
    this->position = Position;
    this->lightNum = lightNumber;
    for(int i = 0; i < 4; i++)
    {
        this->ambientColour[i] = this->diffuseColour[i] = this->specularColour[i] = 1;
    }
    glEnable(this->lightNum);
}

Light::~Light()
{
    //dtor
}

void Light::SetAmbientColour(GLfloat R, GLfloat G, GLfloat B, GLfloat A)
{
    this->ambientColour[0] = R;
    this->ambientColour[1] = G;
    this->ambientColour[2] = B;
    this->ambientColour[3] = A;
    glLightfv(this->lightNum, GL_AMBIENT, this->ambientColour);
}
void Light::SetDiffuseColour(GLfloat R, GLfloat G, GLfloat B, GLfloat A)
{
    this->diffuseColour[0] = R;
    this->diffuseColour[1] = G;
    this->diffuseColour[2] = B;
    this->diffuseColour[3] = A;
    glLightfv(this->lightNum, GL_DIFFUSE, this->diffuseColour);

}
void Light::SetSpecularColour(GLfloat R, GLfloat G, GLfloat B, GLfloat A)
{
    this->specularColour[0] = R;
    this->specularColour[1] = G;
    this->specularColour[2] = B;
    this->specularColour[3] = A;
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
