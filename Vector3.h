#ifndef VECTOR3_H
#define VECTOR3_H
#include "includes.h"
#include <string>

class Vector3
{
public:
	Vector3(float X, float Y, float Z);
    Vector3();
	float x, y, z;

    Vector3 operator+ (const Vector3 rhs); //Vector addition
	Vector3 operator- (const Vector3 rhs); //Vector subtraction
	Vector3 operator* (const float rhs); //Scalar Product (a = a * b)
	Vector3 operator* (const Vector3 rhs); //Inner Product
	Vector3 operator% (const Vector3 rhs); //Cmp Cross Product (a = Cross(a, b))

    Vector3 operator+= (const Vector3 rhs); //Cmp Vector addition
	Vector3 operator-= (const Vector3 rhs); //Cmp Vector subtraction
	Vector3 operator*= (const float rhs); //Cmp Scalar Product (a = a * b)
	Vector3 operator%= (const Vector3 rhs); //Cmp Cross Product (a = Cross(a, b))

    Vector3 operator- ();

    std::string ToString();
    GLfloat* ToGLFloat3();
    GLfloat* ToGLFloat4(float w);

	static Vector3 fromCylindrical(float rho, float phi, float z);
	static Vector3 fromCylindrical(float rho, float phi, float z, Vector3 zDirection);
	static Vector3 fromSpherical(float rho, float theta, float phi);

	static float Dot(Vector3 a, Vector3 b);
	static Vector3 Cross(Vector3 a, Vector3 b);

};

/*
inline functions:
	operator+,
	operator- (binary and unary),
	dot / scalar product (operator*),
	cross (operator%)
*/


#endif // VECTOR3_H
