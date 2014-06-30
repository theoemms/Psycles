#include "includes.h"

Drawable::Drawable()
{
    for(int i = 0; i < 3; i++)
    {
        this->position[i] = 0;
        this->rotation[i] = 0;
    }
}

Drawable::~Drawable()
{

}

void Drawable::Translate()
{
    glTranslatef(this->position[0], this->position[1], this->position[2]);
    glRotatef(this->rotation[0], 1, 0, 0);
    glRotatef(this->rotation[1], 0, 1, 0);
    glRotatef(this->rotation[2], 0, 0, 1);
}

Teapot::Teapot()
{

}

Teapot::~Teapot()
{

}

bool Teapot::Draw() //Matrix mode must be modelview
{
    glPushMatrix();
    this->Translate();
    glFrontFace(GL_CW);
    glutSolidTeapot(1);
    glFrontFace(GL_CCW);
    glPopMatrix();
    return true;
}


Surface::Surface()
{
}

Surface::~Surface()
{
    free(this->points);
    free(this->normals);
}

bool Surface::Draw() //Matrix mode must be modelview
{
    glPushMatrix();
    this->Translate();
    glBegin(GL_TRIANGLES);
    GLfloat* glPoint;
    GLfloat* glNormal;
        for (int i = 0; i < this->numPoints; i++)
        {
            glPoint = this->points[i].ToGLFloat3();
            glNormal = this->normals[i].ToGLFloat3();
            glNormal3fv(glNormal);
            glVertex3fv(glPoint);
            free(glPoint);
            free(glNormal);
        }
    if(this->doubleSided)
    {
        for (int i = this->numPoints - 1; i >=0 ; i--)
        {
            glPoint = this->points[i].ToGLFloat3();
            glNormal = this->normals[i].ToGLFloat3();
            glNormal3fv(glNormal);
            glVertex3fv(glPoint);
            free(glPoint);
            free(glNormal);
        }
    }
    glEnd();
    glPopMatrix();
    return true;
}

Triangle::Triangle()
{
    this->numPoints = 3;
    this->points = (Vector3*) malloc(sizeof(Vector3) * numPoints);
    this->normals = (Vector3*) malloc(sizeof(Vector3) * numPoints);

    this->points[0] = Vector3(-1, 0, 0);
    this->normals[0] = Vector3(0, 0, 1);

    this->points[1] = Vector3(1, 0, 0);
    this->normals[1] = Vector3(0, 0, 1);

    this->points[2] = Vector3(0, 1, 0);
    this->normals[2] = Vector3(0, 0, 1);

    this->doubleSided = true;
}

Triangle::~Triangle()
{

}


Plane::Plane()
{
}

Plane::~Plane()
{

}






