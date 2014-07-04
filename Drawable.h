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
    uint numPoints;
    bool doubleSided;
    Surface();
    virtual ~Surface();
    virtual void Draw();
  protected:
    Vector3* points;
    Vector3* normals;
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
