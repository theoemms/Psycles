#ifndef UPDATABLE_H
#define UPDATABLE_H


class Updatable
{
    public:
        Updatable();
        virtual ~Updatable();
        virtual void Update(float timePassed)=0;
    protected:
    private:
};

class  ScaleAnimation : public Updatable
{
    public:
        ScaleAnimation(float* target, float Speed);
        virtual ~ScaleAnimation();
        virtual void Update(float timePassed);
    protected:
    private:
    float* var;
    float speed;
};




#endif // UPDATABLE_H
