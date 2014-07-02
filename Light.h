#ifndef LIGHT_H
#define LIGHT_H
#include "includes.h"


class Light
{
    public:
        GLenum lightNum;

        Vector3 position;
        bool directional;

        GLfloat diffuseColour[4];
        GLfloat specularColour[4];
        GLfloat ambientColour[4];

        Light(Vector3 Position, bool isDirectional, GLenum lightNumber);
        virtual ~Light();
        void Initialize();
        void GLSetColour();
        void GLSetPosition();

    protected:
    private:
        GLfloat* GetGLPosition();
};

#endif // LIGHT_H
