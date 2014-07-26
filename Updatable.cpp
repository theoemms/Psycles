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

ClampedScaleAnimation::ClampedScaleAnimation(float* target, float Speed, float max, float min, string name) : Updatable(name)
{
    this->var = target;
    this->speed = Speed;
    this->maxValue = max;
    this->minValue = min;
}

ClampedScaleAnimation::~ClampedScaleAnimation()
{}

void ClampedScaleAnimation::Update(float timePassed)
{
    float newValue = *this->var + timePassed * this->speed;
    if (newValue < this->minValue)
    {
        *this->var = minValue;
    }
    else if(newValue > this->maxValue)
    {
        *this->var = this->maxValue;
    }
    else
    {
        *this->var = newValue;
    }
}

SphPolarVectorAddAnimation::SphPolarVectorAddAnimation(Vector3* target, float* Theta, float* Phi, float Speed, string name) : Updatable(name)
{
    this->var = target;
    this->speed = Speed;
    this->theta = Theta;
    this->phi = Phi;
}

SphPolarVectorAddAnimation::~SphPolarVectorAddAnimation(){}

void SphPolarVectorAddAnimation::Update(float deltaT)
{
    *this->var += Vector3::fromSpherical(this->speed, *this->theta, *this->phi) * deltaT;
}
