#include "includes.h"
#include <sstream>
#include <string>

#include<math.h>

using namespace std;

Vector3::Vector3(float X, float Y, float Z) //Constructor
{
    x = X;
    y = Y;
    z = Z;
}

Vector3::Vector3()
{
    x = y = z = 0;
}

Vector3 Vector3::operator+(const Vector3 rhs)
{
    return Vector3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

Vector3 Vector3::operator-(const Vector3 rhs)
{
    return Vector3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}

Vector3 Vector3::operator*(const float rhs)
{
    return Vector3(rhs * this->x, rhs * this->y, rhs * this->z);
}

Vector3 Vector3::operator+= (const Vector3 rhs) //Cmp Vector addition
{
    *this = *this + rhs;
    return *this;
}
Vector3 Vector3::operator-= (const Vector3 rhs) //Cmp Vector subtraction
{
    *this = *this - rhs;
    return *this;
}

Vector3 Vector3::operator*= (const float rhs) //Cmp Scalar Product (a = a * b)
{
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;

    return *this;
}
Vector3 Vector3::operator%= (const Vector3 rhs) //Cmp Cross Product (a = Cross(a, b))
{
    Vector3 Output = Cross(*this, rhs);
    this->x = Output.x;
    this->y = Output.y;
    this->z = Output.z;
    return *this;
}

Vector3 Vector3::operator-()
{
    return *this * -1;
}

string Vector3::ToString()
{
    ostringstream stream;
    stream << "(" << this->x << ", " << this->y << ", " << this->z << ")";
    return stream.str();
}

GLfloat* Vector3::ToGLFloat3()
{
    GLfloat* output = (GLfloat*) malloc(sizeof(GLfloat) * 3);
    output[0] = this->x;
    output[1] = this->y;
    output[2] = this->z;
    return output;
}

GLfloat* Vector3::ToGLFloat4(float w)
{
    GLfloat* output = (GLfloat*) malloc(sizeof(GLfloat) * 4);
    output[0] = this->x;
    output[1] = this->y;
    output[2] = this->z;
    output[3] = w;
    return output;
}


float Vector3::Dot(Vector3 a, Vector3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3::Cross(Vector3 a, Vector3 b)
{
    return Vector3(a.y * b.z - a.z * b.y,
                   a.z * b.x - a.x * b.z,
                   a.x * b.y - a.y * b.x);
}

Vector3 operator*(const Vector3 lhs, const float rhs)
{
    return Vector3(rhs * lhs.x, rhs * lhs.y, rhs * lhs.z);
}

Vector3 operator*(const float lhs, const Vector3 rhs)
{
    return rhs * lhs;
}

Vector3 Vector3::fromSpherical(float rho, float theta, float phi)
{
    return Vector3(rho * cos(theta * 3.14159f / 180) * sin(phi * 3.14159f / 180),
                   rho * sin(-theta * 3.14159f / 180),
                   rho * cos(theta * 3.14159f / 180) * cos(phi * 3.14159f / 180));
}