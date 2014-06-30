#ifndef LIGHT_H
#define LIGHT_H
#include "includes.h"


class Light
{
    public:
        Vector3 position;
        bool directional;

        GLfloat diffuseColour[4];
        GLfloat specularColour[4];
        GLfloat ambientColour[4];

        Light(Vector3 Position, bool isDirectional);
        virtual ~Light();
        void Initialize();

        GLfloat* GetGLPosition();
    protected:
    private:
};

#endif // LIGHT_H
