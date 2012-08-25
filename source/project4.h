//This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
GLfloat ob_diffuse_on[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat ob_diffuse_off[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat ob_specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat ob_ambient_on[] = { 5.0, 5.0, 5.0, 1.0 };
GLfloat ob_ambient_off[] = { 1.0, 1.0, 1.0, 1.0 };

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
void myIdle(void);

#endif
