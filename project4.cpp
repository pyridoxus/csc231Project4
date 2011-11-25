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
void showMenu(void);

// Callbacks
void myDraw();
void keyboard( unsigned char, int, int );
void specialKeyFunc( int key, int x, int y );

int main( int argc, char **argv )
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
	glutSpecialFunc( specialKeyFunc );

	// Menu

  // Main loop
  glutMainLoop();
  return 0;
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
    case 'p':		// display as points
    break;
    case 'w':		// display as wireframe
    break;
    case 'h':		// display as hidden-surface wireframe
    break;
    case 'm':		// display as polygons
    break;
    case 's':		// toggle flat/smooth shading
    break;
    case 't':		// display with 2D texture
    break;
    case 'e':		// display with Environment texture
    break;
    case 'b':		// display with 2D and Environment texture
    break;
    case 'A':		// start animated spin about Y axis
    break;
    case 'S':		// stop animated spin about Y axis
    break;
    case 'R':		// reset animated spin about Y axis
    break;
 	}

  // Redraw the scene
  glutPostRedisplay();
}

void showMenu(void)
{
	cout << "key  function" << endl;
	cout << " p - display as points" << endl;
	cout << " w - display as wireframe" << endl;
	cout << " h - display as hidden-surface wireframe" << endl;
	cout << " m - display as polygons" << endl;
	cout << " s - toggle flat/smooth shading" << endl;
	cout << " t - display with 2D texture" << endl;
	cout << " e - display with Environment texture" << endl;
	cout << " b - display with 2D and Environment texture" << endl;
	cout << " A - start animated spin about Y axis" << endl;
	cout << " S - stop animated spin about Y axis" << endl;
	cout << " R - reset animated spin about Y axis" << endl;
	cout << " q - exit the program" << endl;
 	return;
}

void specialKeyFunc( int key, int x, int y )
{
	switch(key)
	{
		case GLUT_KEY_LEFT:		// Translate along –x axis
		break;
		case GLUT_KEY_RIGHT:	// Translate along +x axis
		break;
		case GLUT_KEY_DOWN:		// Translate along –y axis
		break;
		case GLUT_KEY_UP:			// Translate along +y axis
		break;
		case GLUT_KEY_PAGE_UP:	// Translate along –z axis
		break;
		case GLUT_KEY_PAGE_DOWN:	// Translate along +z axis	}
		break;
	}
	return;
}
