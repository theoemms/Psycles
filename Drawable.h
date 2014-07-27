#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "includes.h"

class Drawable
{
    public:
        Vector3 position;
        Vector3 rotation;
        float scale;
        Drawable();
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
        CompoundDrawable(uint numChildren);
        virtual ~CompoundDrawable();
        virtual void Draw();
    protected:
        uint size;
};

class Teapot : public Drawable
{
  public:
    Teapot();
    virtual ~Teapot();
    virtual void Draw();
  protected:
  private:
};

class Surface : public Drawable
{
  public:
    bool doubleSided;
    Surface();
    Surface(Vector3* pointData, Vector3* normalData, GLuint* indexData);
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
    Triangle();
    virtual ~Triangle();
};

class Plane : public Surface
{
public:
    Plane();
    virtual ~Plane();
};
#endif // DRAWABLE_H
