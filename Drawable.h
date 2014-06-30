#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "includes.h"

class Drawable
{
    public:
        float position[3];
        float rotation[3];
        Drawable();
        virtual ~Drawable();
        virtual bool Draw() = 0;
        virtual void Translate();
    protected:
    private:
};


class Teapot : public Drawable
{
  public:
    Teapot();
    virtual ~Teapot();
    virtual bool Draw();
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
    virtual bool Draw();
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
