#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "includes.h"
#include <string.h>

using namespace std;

class Drawable
{
    public:
        string name;
        Vector3 position;
        Vector3 rotation;
        float scale;
        Drawable(string Name);
        virtual ~Drawable();
        virtual void Draw() = 0;
        virtual void Translate();
    protected:
    private:
};

class CompoundDrawable : public Drawable
{
    public:
        Drawable** children;
        CompoundDrawable(uint numChildren, string name);
        virtual ~CompoundDrawable();
        virtual void Draw();
    protected:
        uint size;
};

class Teapot : public Drawable
{
  public:
    Teapot(string name);
    virtual ~Teapot();
    virtual void Draw();
  protected:
  private:
};

class Surface : public Drawable
{
  public:
    bool doubleSided;
    Surface(string name);
    Surface(Vector3* pointData, Vector3* normalData, GLuint* indexData, string name);
    virtual ~Surface();
    virtual void Draw();
    Surface Subdivide(uint n);
  protected:
    uint numPoints;
    uint numIndices;
    
    Vector3* points;
    GLfloat* pointsBuffer;
    
    Vector3* normals;
    GLfloat* normalsBuffer;
    
    GLuint* indices;
    
    void GenBuffers();
};

class Triangle : public Surface
{
  public:
    Triangle(string name);
    virtual ~Triangle();
};

class Plane : public Surface
{
public:
    Plane(string name);
    virtual ~Plane();
};
#endif // DRAWABLE_H
