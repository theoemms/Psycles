#include "includes.h"
#include<string>
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

FlythroughCamera::FlythroughCamera(Vector3 position, float theta0, float phi0, float Sensitivity, float Speed, float FOV, float near, float far) : Camera(position, Vector3(0, 0, 0), true, FOV, near, far)
{
    //Set initial values of theta and phi.
    this->theta = theta0;
    this->phi = phi0;
    
    this->sensitivity = Sensitivity;
    this->speed = Speed;
    
    //Set up the keyboard input and register them in the game.
    this->rotateLeftAnim = new ScaleAnimation(&this->phi, this->sensitivity, "Camera Rotate Left");
    this->rotateRightAnim = new ScaleAnimation(&this->phi, -this->sensitivity, "Camera Rotate Right");
    this->rotateUpAnim = new ClampedScaleAnimation(&this->theta, this->sensitivity, 90, -90, "Camera Rotate Up");
    this->rotateDownAnim = new ClampedScaleAnimation(&this->theta, -this->sensitivity, 90, -90, "Camera Rotate Down");
    this->translateForwardsAnim = new SphPolarVectorAddAnimation(&this->position, &this->theta, &this->phi, -this->speed, "Camera Translate Forwards");
    this->translateBackwardsAnim = new SphPolarVectorAddAnimation(&this->position, &this->theta, &this->phi, this->speed, "Camera Translate Backwarsds)");
    
    this->forwardsKey = new OnKeyHold(' ', translateForwardsAnim, "Camera Forwards Key");
    this->backwardsKey = new OnKeyHold('x', translateBackwardsAnim, "Camera Backwards Key");
    this->rotateLeftKey = new OnKeyHold('a', rotateLeftAnim, "Camera Rotate Left Key");
    this->rotateRightKey = new OnKeyHold('d', rotateRightAnim, "Camera Rotate Right Key");
    this->rotateUpKey = new OnKeyHold('s', rotateUpAnim, "Camera Rotate Up Key");
    this->rotateDownKey = new OnKeyHold('w', rotateDownAnim, "Camera Rotate Down Key");
    
    game->RegisterKeyboardEvent(forwardsKey);
    game->RegisterKeyboardEvent(backwardsKey);
    game->RegisterKeyboardEvent(rotateLeftKey);
    game->RegisterKeyboardEvent(rotateRightKey);
    game->RegisterKeyboardEvent(rotateUpKey);
    game->RegisterKeyboardEvent(rotateDownKey);
}

FlythroughCamera::~FlythroughCamera()
{
    delete this->forwardsKey;
    delete this->rotateLeftKey;
    delete this->rotateRightKey;
    delete this->rotateUpKey;
    delete this->rotateDownKey;
    
    delete this->rotateLeftAnim;
    delete this->rotateRightAnim;
    delete this->rotateUpAnim;
    delete this->rotateDownAnim;
    delete this->translateForwardsAnim;
}

void FlythroughCamera::Translate()
{
    glRotatef(-this->theta, 1, 0, 0);
    glRotatef(-this->phi, 0, 1, 0);
    glTranslatef(-this->position.x, -this->position.y, -this->position.z);
}
