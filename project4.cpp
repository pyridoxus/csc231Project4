#include <iostream>
using namespace std;
#include <GL/glut.h>
#include <GL/glext.h>

// NOTE: Download header above (glext.h) FROM http://www.opengl.org/registry/ and
// place in directory C:\Program Files\Microsoft Visual Studio 9.0\VC\include\GL

string texFile = "C:\\Home\\Class\\CSC231\\Projects\\Textures\\brick.sgi";
string envFile = "C:\\Home\\Class\\CSC231\\Projects\\Textures\\spheremap.sgi";
float fov = 45.0;
float aspect = 1.333;
float nearClip = 0.01;
float farClip = 10000.0;
int width, height;
GLubyte *texels  = NULL;
GLubyte *texelsR = NULL;
float bg[3] = { 0.5, 0.5, 0.5 };

// Functions
unsigned *read_texture(char *, int *, int * );

// Callbacks
void myDraw();
void keyboard( unsigned char, int, int );


void main( int argc, char **argv )
{
  // Read polygonal mesh

	// Compute polygon and vertex normals

  // Initialize window system
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
  glutInitWindowSize( 640, 480 );
  glutCreateWindow( "Project 4" );

  // Projection
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( fov, aspect, nearClip, farClip );

	// Viewing
	glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glTranslatef( 0, 0, -15 );

  // Hidden surface z-buffering
  glEnable( GL_DEPTH_TEST );

	// Select shading model

	// Define lights

	// Enable lighting model

	// Texture creation

	// 2D texture
	texels  = (GLubyte *)read_texture( (char *)texFile.c_str(), &width, &height );

	// 2D texture specifications

	// Environment texture
	texelsR = (GLubyte *)read_texture( (char *)envFile.c_str(), &width, &height );

	// Environment texture specifications

  // Callbacks
  glutDisplayFunc( myDraw );
  glutKeyboardFunc( keyboard );

	// Menu

  // Main loop
  glutMainLoop();
}

// Display callback
void myDraw()
{
  // Clear the screen
  glClearColor( bg[0], bg[1], bg[2], 1.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Draw scene

  // Swap buffers
  glutSwapBuffers();
}

// Keyboard callback
void keyboard( unsigned char key, int x, int y )
{
  // Process entries
  switch( key )
    {
    case 'q':							// Quit
      exit(1);
      break;
	}

  // Redraw the scene
  glutPostRedisplay();
}

