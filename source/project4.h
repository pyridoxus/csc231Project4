#ifndef PROJECT4_H_
#define PROJECT4_H_

#include <iostream>
using namespace std;
#include <GL/glut.h>
#include <GL/glext.h>
#include <stdlib.h>
#include "readSGI.h"
#include "GLObject.h"

// NOTE: Download header above (glext.h) FROM http://www.opengl.org/registry/ and
// place in directory C:\Program Files\Microsoft Visual Studio 9.0\VC\include\GL

// Using Linux paths and toolchain...
String texFile = "textures/marble.sgi";
String envFile = "textures/spheremap.sgi";
String objFile = "objects/buckyball.obj";

float fov = 45.0;
float aspect = 1.333;
float nearClip = 0.01;
float farClip = 10000.0;
int width, height;
GLubyte *texels  = NULL;
GLubyte *texelsR = NULL;
float bg[3] = { 0.5, 0.5, 0.5 };
GLObject glObject(objFile);	// Initialize the object

// Functions
unsigned *read_texture(char *, int *, int * );
void showMenu(void);

// Callbacks
void myDraw();
void keyboard( unsigned char, int, int );
void specialKeyFunc( int key, int x, int y );

#endif
