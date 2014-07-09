#include "includes.h"
#include<string>

using namespace std;

Updatable::Updatable(string Name)
{
    this->name = Name;
}

Updatable::~Updatable()
{
    //dtor
}

ScaleAnimation::ScaleAnimation(float* target, float Speed, string name) : Updatable(name)
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
