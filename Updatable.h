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
        ScaleAnimation(float* target, float Speed, string name);
        virtual ~ScaleAnimation();
        virtual void Update(float timePassed);
    protected:
    private:
    float* var;
    float speed;
};




#endif // UPDATABLE_H
