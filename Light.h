#ifndef LIGHT_H
#define LIGHT_H
#include "includes.h"


class Light
{
    public:
        GLenum lightNum;

        Vector3 position;
        bool directional;

        Light(Vector3 Position, bool isDirectional, GLenum lightNumber);
        virtual ~Light();
        void Initialize();

        void SetAmbientColour(GLfloat R, GLfloat G, GLfloat B, GLfloat A);
        void SetDiffuseColour(GLfloat R, GLfloat G, GLfloat B, GLfloat A);
        void SetSpecularColour(GLfloat R, GLfloat G, GLfloat B, GLfloat A);

        void GLSetPosition();

    protected:
    private:
        GLfloat specularColour[4];
        GLfloat ambientColour[4];
        GLfloat diffuseColour[4];

        GLfloat* GetGLPosition();
};

#endif // LIGHT_H
