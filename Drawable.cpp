#include "includes.h"

Drawable::Drawable() //Set the position and rotation to (0, 0, 0)
{
    this->position = Vector3(0, 0, 0);
    this->rotation = Vector3(0, 0, 0);
    this->scale = 1;
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
    glScalef(this->scale, this->scale, this->scale);
}

CompoundDrawable::CompoundDrawable(uint numChildren)
{
    this->size = numChildren;
    this->children = (Drawable**) malloc(this->size * sizeof(Drawable*));
}

CompoundDrawable::~CompoundDrawable()
{
    free(this->children);
}

void CompoundDrawable::Draw()
{
    this->Translate();
    for(int i = 0; i < this->size; i++)
    {
        this->children[i]->Draw();
    }
}

Teapot::Teapot() //Teapot is simple, it just uses the default constructor
{

}

Teapot::~Teapot() //Nothing to free here
{

}

void Teapot::Draw() //Draw a teapot (Assumes matrix mode is modelview and
                    //translation to scene coordinates had been made)
{
    this->Translate(); //Do translation.
    glFrontFace(GL_CW); //glutSolidTeapot has backwards vertex winding.
    glutSolidTeapot(1); //Draw teapot.
    glFrontFace(GL_CCW); //restore normal vertes winding
}


Surface::Surface() //Nothing to be done. (This should allow an array of points and normals to be passed in)
{
}

Surface::Surface(Vector3* pointData, Vector3* normalData, GLuint* indexData)
{
    this->numPoints = sizeof(pointData) / sizeof(Vector3);
    this->points = pointData;
    this->normals = normalData;
    this->indices = indexData;
    
    this->GenBuffers();
}

void Surface::GenBuffers()
{
    GLfloat* glPoint;
    GLfloat* glNormal;
    
    this->pointsBuffer = (GLfloat*) malloc(3 * this->numPoints * sizeof(GLfloat));
    this->normalsBuffer = (GLfloat*) malloc(3 * this->numPoints * sizeof(GLfloat));
    
    for (int i = 0; i < this->numPoints; i++) //Go through the vertices in order
    {
        glPoint = this->points[i].ToGLFloat3(); //Make our Vector3 into a Glfloat3*
        glNormal = this->normals[i].ToGLFloat3();
        
        this->pointsBuffer[3 * i]       = glPoint[0];
        this->pointsBuffer[3 * i + 1]   = glPoint[1];
        this->pointsBuffer[3 * i + 2]   = glPoint[2];
        
        this->normalsBuffer[3 * i]       = glNormal[0];
        this->normalsBuffer[3 * i + 1]   = glNormal[1];
        this->normalsBuffer[3 * i + 2]   = glNormal[2];
        
        free(glPoint); //Free the memory
        free(glNormal);
    }
}

Surface::~Surface() //The points and normals are set by malloc so must be freed
{
    free(this->points);
    free(this->normals);
    free(this->indices);
    free(this->pointsBuffer);
    free(this->normalsBuffer);
}

void Surface::Draw() //Iterate over points and draw.
{
    this->Translate();
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, this->pointsBuffer);
        glNormalPointer(GL_FLOAT, 0, this->normalsBuffer);
    
        glDrawElements(GL_TRIANGLES, this->numIndices, GL_UNSIGNED_INT, this->indices);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

Triangle::Triangle()//This function is pretty self exaplanatory. It sets the triangle's vertices and makes it double sided.
{
    this->numPoints = 3;
    this->numIndices = 3;
    
    this->points = (Vector3*) malloc(sizeof(Vector3) * this->numPoints);
    this->normals = (Vector3*) malloc(sizeof(Vector3) * this->numPoints);
    this->indices = (GLuint*) malloc(this->numIndices * sizeof(GLuint));
    
    this->points[0] = Vector3(-1, 0, 0);
    this->normals[0] = Vector3(0, 0, 1);

    this->points[1] = Vector3(1, 0, 0);
    this->normals[1] = Vector3(0, 0, 1);

    this->points[2] = Vector3(0, 1, 0);
    this->normals[2] = Vector3(0, 0, 1);

    this->indices[0] = 0;
    this->indices[1] = 1;
    this->indices[2] = 2;

    this->GenBuffers();
}

Triangle::~Triangle()
{
}


Plane::Plane()
{
    this->numPoints = 4;
    this->numIndices = 6;
    
    this->points = (Vector3*) malloc(sizeof(Vector3) * this->numPoints);
    this->normals = (Vector3*) malloc(sizeof(Vector3) * this->numPoints);
    this->indices = (GLuint*) malloc(this->numIndices * sizeof(GLuint));
    
    this->points[0] = Vector3(-1, 0, -1);
    this->normals[0] = Vector3(0, 1, 0);
    
    this->points[1] = Vector3(-1, 0, 1);
    this->normals[1] = Vector3(0, 1, 0);

    this->points[2] = Vector3(1, 0, 1);
    this->normals[2] = Vector3(0, 1, 0);
    
    this->points[3] = Vector3(1, 0, -1);
    this->normals[3] = Vector3(0, 1, 0);
    
    this->indices[0] = 0;
    this->indices[1] = 1;
    this->indices[2] = 3;
    
    this->indices[3] = 1;
    this->indices[4] = 2;
    this->indices[5] = 3;
    
    this->GenBuffers();
}

Plane::~Plane()
{

}






