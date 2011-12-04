#include "project4.h"

int main( int argc, char **argv )
{
  // Read polygonal mesh
	glObject.print();
	// Compute polygon and vertex normals

  // Initialize window system
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
  glutInitWindowSize( 800, 600 );
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
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glShadeModel(GL_SMOOTH);

	// Define lights
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	// Enable lighting model
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

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
	showMenu();

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
  glColor3f(1.0, 1.0, 1.0);
  drawLight();
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glObject.draw();
//  cout << "Draw" << endl;
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
    	glObject.setDrawMode(POINTS);
    break;
    case 'w':		// display as wireframe
    	glObject.setDrawMode(WIREFRAME);
    break;
    case 'h':		// display as hidden-surface wireframe
    	glObject.setDrawMode(WIREFRAME | HIDDENSURFACE);
    break;
    case 'm':		// display as polygons
    	glObject.setDrawMode(POLYGON);
    break;
    case 's':		// toggle flat/smooth shading
    break;
    case 't':		// display with 2D texture
    	glObject.setDrawMode(TEXTURE);
    break;
    case 'e':		// display with Environment texture
    	glObject.setDrawMode(ENVIRONMENT);
    break;
    case 'b':		// display with 2D and Environment texture
    	glObject.setDrawMode(TEXTURE | ENVIRONMENT);
    break;
    case 'A':		// start animated spin about Y axis
    	glObject.spinY(1);
    break;
    case 'S':		// stop animated spin about Y axis
    	glObject.spinY(0);
    break;
    case 'R':		// reset animated spin about Y axis
    	glObject.spinY(-1);
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
	cout << " Left Arrow  - Translate light along –x axis" << endl;
	cout << " Right Arrow - Translate light along +x axis" << endl;
	cout << " Down Arrow  - Translate light along –y axis" << endl;
	cout << " Up Arrow    - Translate light along +y axis" << endl;
	cout << " Page Up     - Translate light along –z axis" << endl;
	cout << " Page Down   - Translate light along +z axis" << endl;
	cout << " q - exit the program" << endl;
 	return;
}

void specialKeyFunc( int key, int x, int y )
{
	switch(key)
	{
		case GLUT_KEY_LEFT:			// translate along -x axis
			light_position[0]--;
		break;
		case GLUT_KEY_RIGHT:		// translate along +x axis
			light_position[0]++;
		break;
		case GLUT_KEY_DOWN:			// translate along -y axis
			light_position[1]--;
		break;
		case GLUT_KEY_UP:			  // translate along +y axis
			light_position[1]++;
		break;
		case GLUT_KEY_PAGE_UP:  // translate along -z axis
			light_position[2]--;
		break;
		case GLUT_KEY_PAGE_DOWN:// translate along +z axis
			light_position[2]++;
		break;
	}
	// Redraw the scene
  glutPostRedisplay();
	return;
}

void drawLight(void)
{
  glPushMatrix();
  glLoadName( LIGHT );      // Load picking id
  glTranslatef( light_position[0], light_position[1], light_position[2] );
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	// Draw light
  if(glIsEnabled(GL_LIGHT0))
  {
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ob_diffuse_on);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ob_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ob_ambient_on);
    glutSolidSphere( 0.5, 10, 10 );
  }
  else
  {
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ob_diffuse_off);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ob_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ob_ambient_off);
		glutWireSphere(0.5, 10, 10);
  }
  glPopMatrix();
  return;
}
