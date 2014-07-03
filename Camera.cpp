#include "includes.h"

Camera::Camera(Vector3 Position, Vector3 TargOrRot, bool Track, GLfloat FOV, GLfloat near, GLfloat far)
{
    this->position = Position;
    this->up = Vector3(0, 1, 0);

    if(Track)
    {
        this->trackTarget = TargOrRot;
        this->rotation = Vector3(0, 0, 0);
    }
    else
    {
        this->trackTarget = Vector3(0, 0, 0);
        this->rotation = TargOrRot;
    }
    this->fieldOfView = FOV;
    this->tracking = Track;
    this->nearDistance = near;
    this->farDistance = far;
}

void Camera::Translate()
{
    if(this->tracking)
    {
        gluLookAt(this->position.x, this->position.y, this->position.z,
                  this->trackTarget.x, this->trackTarget.y, this->trackTarget.z,
                  this->up.x, this->up.y, this->up.z);
    }
    else
    {
        glRotatef(-this->rotation.x, 1, 0, 0);
        glRotatef(-this->rotation.y, 0, 1, 0);
        glRotatef(-this->rotation.z, 0, 0, 1);
        glTranslatef(-this->position.x, -this->position.y, -this->position.z);
    }
}

void Camera::SetProjection(GLfloat aspectRatio)
{
    glLoadIdentity();
    gluPerspective(this->fieldOfView, aspectRatio, this->nearDistance, this->farDistance);
}

Camera::~Camera()
{
    //dtor
}
