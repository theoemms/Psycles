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
        virtual void Translate();
        void SetProjection(GLfloat aspectRatio);
    protected:
    private:
};

class FlythroughCamera : public Camera
{
    public:
        float theta;
        float phi;
        float sensitivity;
        float speed;
    
        FlythroughCamera(Vector3 position, float theta0, float phi0, float Sensitivity, float Speed, float FOV, float near, float far);
        virtual ~FlythroughCamera();
        virtual void Translate();
    
    private:
        OnKeyHold* forwardsKey;
        OnKeyHold* rotateLeftKey;
        OnKeyHold* rotateRightKey;
        OnKeyHold* rotateUpKey;
        OnKeyHold* rotateDownKey;
        
        ScaleAnimation* rotateLeftAnim;
        ScaleAnimation* rotateRightAnim;
        ClampedScaleAnimation* rotateUpAnim;
        ClampedScaleAnimation* rotateDownAnim;
        SphPolarVectorAddAnimation* translateForwardsAnim;
};

#endif // CAMERA_H
