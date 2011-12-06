#include "project4.h"

int main( int argc, char **argv )
{
  // Read polygonal mesh	(occurs before main starts, see project4.h)
	// Compute polygon and vertex normals (occurs before main starts)
	// The GLObject is global.

	height = 320;
	width = 400;

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

  // Improves specular lighting
  glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR );

  // Enable lighting model
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

	// Texture creation
  glGenTextures( NUM_TEXTURES, glObject.texName );

	// 2D texture
	texels  = (GLubyte *)read_texture( (char *)texFile.c_str(), &width, &height );

	// 2D texture specifications
	glBindTexture( GL_TEXTURE_2D, glObject.texName[MARBLE] );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, texels );


	// Environment texture
	texelsR = (GLubyte *)read_texture( (char *)envFile.c_str(), &width, &height );

	// Environment texture specifications
  glBindTexture( GL_TEXTURE_2D, glObject.texName[ENVIRON_IMG] );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
  glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
  		GL_UNSIGNED_BYTE, texelsR );

  // Callbacks
  glutDisplayFunc( myDraw );
  glutKeyboardFunc( keyboard );
	glutSpecialFunc( specialKeyFunc );
  glutCreateMenu( menu );
	glutAddMenuEntry( "display as points (or 'p' key)", 1 );
	glutAddMenuEntry( "display as wireframe (or 'w' key)", 2 );
	glutAddMenuEntry( "display as hidden-surface wireframe (or 'h' key)", 3 );
	glutAddMenuEntry( "display as polygons (or 'm' key)", 4 );
	glutAddMenuEntry( "toggle flat/smooth shading (or 's' key)", 5 );
	glutAddMenuEntry( "display with 2D texture (or 't' key)", 6 );
	glutAddMenuEntry( "display with Environment texture (or 'e' key)", 7 );
	glutAddMenuEntry( "display with 2D and Environment texture (or 'b' key)", 8 );
	glutAddMenuEntry( "start animated spin about Y axis (or 'A' key)", 9 );
	glutAddMenuEntry( "stop animated spin about Y axis (or 'S' key)", 10 );
	glutAddMenuEntry( "reset animated spin about Y axis (or 'R' key)", 11 );
	glutAddMenuEntry( "exit the program (or 'q' key)", 12 );
  glutAttachMenu( GLUT_RIGHT_BUTTON );

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
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  drawLight();
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
    	glObject.toggleSmooth();
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
      glutIdleFunc(myIdle);
    break;
    case 'S':		// stop animated spin about Y axis
      glutIdleFunc(NULL);
    break;
    case 'R':		// reset animated spin about Y axis
      glutIdleFunc(NULL);
    	glObject.setSpin(-1);
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

void menu( int value )
{
	switch(value)
	{
		case 1:		// display as points
    	glObject.setDrawMode(POINTS);
		break;
		case 2:		// display as wireframe
    	glObject.setDrawMode(WIREFRAME);
		break;
		case 3:		// display as hidden-surface wireframe
    	glObject.setDrawMode(WIREFRAME | HIDDENSURFACE);
		break;
		case 4:		// display as polygons
    	glObject.setDrawMode(POLYGON);
		break;
		case 5:		// toggle flat/smooth shading
    	glObject.toggleSmooth();
		break;
		case 6:		// display with 2D texture
    	glObject.setDrawMode(TEXTURE);
		break;
		case 7:		// display with Environment texture
    	glObject.setDrawMode(ENVIRONMENT);
		break;
		case 8:		// display with 2D and Environment texture
    	glObject.setDrawMode(TEXTURE | ENVIRONMENT);
		break;
		case 9:		// start animated spin about Y axis
      glutIdleFunc(myIdle);
		break;
		case 10:	// stop animated spin about Y axis
      glutIdleFunc(NULL);
		break;
		case 11:	// reset animated spin about Y axis
      glutIdleFunc(NULL);
    	glObject.setSpin(-1);
		break;
		case 12:	// Quit
      exit(1);
		break;
	}
  // Redraw the scene
  glutPostRedisplay();
	return;
}

// Idle function callback
void myIdle(void)
{
	glObject.setSpin(1);
	myDraw();
  return;
}

