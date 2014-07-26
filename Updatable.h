#ifndef UPDATABLE_H
#define UPDATABLE_H
#include<string>

using namespace std;

class Updatable
{
    public:
        string name;
    
        Updatable(string name);
        virtual ~Updatable();
        virtual void Update(float timePassed)=0;
    protected:
    private:
};

class  ScaleAnimation : public Updatable
{
    public:
        float speed;
    
        ScaleAnimation(float* target, float Speed, string name);
        virtual ~ScaleAnimation();
        virtual void Update(float timePassed);
    protected:
    private:
        float* var;
};

class ClampedScaleAnimation : public Updatable
{
    public:
        float speed;
        float maxValue;
        float minValue;
    
        ClampedScaleAnimation(float* target, float Speed, float max, float min, string name);
        virtual ~ClampedScaleAnimation();
        virtual void Update(float timePassed);
    protected:
    private:
        float* var;
};

class SphPolarVectorAddAnimation : public Updatable
{
public:
    float* theta;
    float* phi;
    float speed;
    
    SphPolarVectorAddAnimation(Vector3* target, float* Theta, float* phi, float Speed, string name);
    virtual ~SphPolarVectorAddAnimation();
    virtual void Update(float timePassed);
protected:
private:
    Vector3* var;
};

#endif // UPDATABLE_H
