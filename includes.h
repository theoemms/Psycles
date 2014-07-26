#ifndef INCLUDES_H
#define INCLUDES_H

#define OSX


#ifdef __APPLE__
#include<OpenGL/gl.h>
#include<OpenGL/glu.h>
#include<GLUT/glut.h>
typedef unsigned int uint;
#else
#include<GL/glut.h>
#endif


#include "Vector3.h"
#include "Globals.h"
#include "Drawable.h"
#include "Updatable.h"
#include "KeyboardEvent.h"
#include "Light.h"
#include "Camera.h"
#include "Game.h"

#endif
