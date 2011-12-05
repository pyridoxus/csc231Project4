#ifndef PROJECT4_H_
#define PROJECT4_H_

#include <iostream>
using namespace std;
#include <stdlib.h>
#include "readSGI.h"
#include "GLObject.h"

#define LIGHT 1

// NOTE: Download header above (glext.h) FROM http://www.opengl.org/registry/ and
// place in directory C:\Program Files\Microsoft Visual Studio 9.0\VC\include\GL

// Using Linux paths and toolchain...
String texFile = "textures/marble.sgi";
String envFile = "textures/spheremap.sgi";
String objFile = "objects/buckyball.obj";

// Initial light position
GLfloat light_position[] = { 3.0, 3.0, 3.0, 0.0 };

// Light properties
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_ambient[] = { 0.05, 0.05, 0.05, 1.0 };

// Light object properties
GLfloat ob_diffuse_on[] = { 0.7, 0.7, 0.2, 1.0 };
GLfloat ob_diffuse_off[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat ob_specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat ob_ambient_on[] = { 7.0, 7.0, 2.0, 1.0 };
GLfloat ob_ambient_off[] = { 7.0, 7.0, 7.0, 1.0 };

float fov = 30.0;
float aspect = 1.333;
float nearClip = 0.01;
float farClip = 10000.0;
int width, height;
//GLubyte texels[64][64][3];
GLubyte *texels  = NULL;
GLubyte *texelsR = NULL;
float bg[3] = { 0.5, 0.5, 0.5 };
GLObject glObject(objFile);	// Initialize the global object

// Functions
unsigned *read_texture(char *, int *, int * );
void showMenu(void);
void drawLight(void);

// Callbacks
void myDraw();
void keyboard( unsigned char, int, int );
void specialKeyFunc( int key, int x, int y );
void menu( int );

#endif
