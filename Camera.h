#ifndef CAMERA_H
#define CAMERA_H


class Camera
{
    public:
        Vector3 position;

        Vector3 trackTarget; //Where the camera looks if tracking == true
        Vector3 up; //The up direction from the camera's perspective, used if tracking == true

        Vector3 rotation;   //The cameras location, used if tracking == false

        bool tracking;

        GLfloat nearDistance;
        GLfloat farDistance;

        GLfloat fieldOfView;

        Camera(Vector3 Position, Vector3 TargOrRot, bool Track, GLfloat FOV, GLfloat near, GLfloat far);
        virtual ~Camera();

        void Translate();
        void SetProjection(GLfloat aspectRatio);
    protected:
    private:
};

#endif // CAMERA_H
