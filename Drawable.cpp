#include "includes.h"

Drawable::Drawable() //Set the position and rotation to (0, 0, 0)
{
    this->position = Vector3(0, 0, 0);
    this->rotation = Vector3(0, 0, 0);
}

Drawable::~Drawable() //Nothing to free here
{

}

void Drawable::Translate() //Perform the default translation.
{
    glTranslatef(this->position.x, this->position.y, this->position.z);
    glRotatef(this->rotation.x, 1, 0, 0);
    glRotatef(this->rotation.y, 0, 1, 0);
    glRotatef(this->rotation.z, 0, 0, 1);
}

Teapot::Teapot() //Teapot is simple, it just uses the default constructor
{

}

Teapot::~Teapot() //Nothing to free here
{

}

bool Teapot::Draw() //Draw a teapot (Assumes matrix mode is modelview and
                    //translation to scene coordinates had been made)
{
    glPushMatrix(); //Ensure only this object is translated by saving the last translation
    this->Translate(); //Do translation.
    glFrontFace(GL_CW); //glutSolidTeapot has backwards vertex winding.
    glutSolidTeapot(1); //Draw teapot.
    glFrontFace(GL_CCW); //restore normal vertes winding
    glPopMatrix(); //Restore the old translation matrix
    return true;
}


Surface::Surface() //Nothing to be done. (This should allow an array of points and normals to be passed in)
{
}

Surface::~Surface() //The points and normals are set by malloc so must be freed
{
    free(this->points);
    free(this->normals);
}

bool Surface::Draw() //Iterate over points and draw.
{
    //See comments in Teapot::Draw for exaplanation:
    glPushMatrix();
    this->Translate();
    glBegin(GL_TRIANGLES);

    //We must save these pointers so that they can be freed
    GLfloat* glPoint;
    GLfloat* glNormal;
        for (int i = 0; i < this->numPoints; i++) //Go through the vertices in order
        {
            glPoint = this->points[i].ToGLFloat3(); //Make our Vector3 into a Glfloat3*
            glNormal = this->normals[i].ToGLFloat3();
            glNormal3fv(glNormal); //Set the corresponding normal
            glVertex3fv(glPoint); //Draw the vertex
            free(glPoint); //Free the memory
            free(glNormal);
        }
    if(this->doubleSided) //If the surface is two sided draw all the faces again but facing backwards
    {
        for (int i = this->numPoints - 1; i >=0 ; i--)//Go through vertices backwards
        {
            glPoint = this->points[i].ToGLFloat3();
            glNormal = (-this->normals[i]).ToGLFloat3(); //Draw with normals reversed
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

Triangle::Triangle()//This function is pretty self exaplanatory. It sets the triangle's vertices and makes it double sided.
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






