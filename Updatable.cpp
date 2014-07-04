#include "includes.h"

Updatable::Updatable()
{
    //ctor
}

Updatable::~Updatable()
{
    //dtor
}

ScaleAnimation::ScaleAnimation(float* target, float Speed)
{
    this->var = target;
    this->speed = Speed;
}

ScaleAnimation::~ScaleAnimation()
{}

void ScaleAnimation::Update(float timePassed)
{
    *this->var += timePassed * this->speed;
}
