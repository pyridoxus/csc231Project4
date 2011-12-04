#include "GLObject.h"

// Specify material properties
GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shininess[] = { 100.0 };
// Specify hidden surface properties
GLfloat h_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat h_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat h_specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat h_shininess[] = { 0.0 };


GLObject::GLObject(String objFile)
{
	char s[256];
	String st, dataType;
	Polygon tempPoly;
	TextureVertex tempTVertex;
	Point tempPoint;
	fstream file(objFile.c_str(), fstream::in);
	while(file.good())
	{
		file.getline(s, 256);	// Get line
		st.assign(s);
		dataType = st.split(' ');
		if(!dataType.compare("v"))
		{
			tempPoint.setPoint(st);	// Process string into floats
			this->points.push_back(tempPoint);		// Store the floats
		}
		else if(!dataType.compare("vt"))
		{
			tempTVertex.setUV(st);	// Process string into floats
			this->tvertex.push_back(tempTVertex);	// Store the floats
		}
		else if(!dataType.compare("f"))
		{
			tempPoly.setPolygon(st);	// Process string into indices (vertex/texture)
			this->calcNormal(&tempPoly);	// Find the normal
			this->mesh.push_back(tempPoly);	// Store indices
		}
	}
	cout << "Number of polygons: " << this->mesh.size() << endl;
	file.close();
	this->spinMode = 0;
	this->angleY = 0.0;
	this->drawMode = POINTS;
	for(int a = 0; a < 3; a++)
	{
		bg[a] = 0.5;
		fg[a] = 1.0;
	}
	this->factor = this->units = 1.0;
	return;
}

GLObject::~GLObject()
{
	cout << "Object destructor" << endl;
	this->mesh.clear();	// Calls the mesh destructors.
	this->tvertex.clear();	// Calls the tvertex destructors.
	this->points.clear();	// Calls the point destructors.
	return;
}

void GLObject::print(void)
{
  vector<TextureVertex>::iterator tviter;
  vector<Polygon>::iterator polyIter;
  vector<Point>::iterator pointIter;
  int a;

  for(pointIter = this->points.begin(); pointIter < this->points.end();
  		pointIter++)
  {
  	cout << "(" << pointIter->getX() << ", " << pointIter->getY() << ", " << \
  			pointIter->getZ()<< ")" << endl;
  }
  for(tviter = this->tvertex.begin(); tviter < this->tvertex.end(); tviter++)
  {
  	cout << "(" << tviter->getU() << ", " << tviter->getV() << ")" << endl;
  }
  for(polyIter = this->mesh.begin(); polyIter < this->mesh.end(); polyIter++)
  {
  	for(a = 0; a < 3; a++)
  	{
  		cout << polyIter->getVertex(a)->pointIndex << "/";
  		cout << polyIter->getVertex(a)->textureIndex;
  		if(a < 2) cout << ", ";
  		else cout << endl;
  	}
  }
}

void GLObject::draw(void)
{
  vector<Polygon>::iterator polyIter;
	int pidx, a, glMode, b;
	Point p;
	Vector3D *n;
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	this->setSpin();
	for(b = 0; b < 2; b++)
	{
		glMode = this->getGLMode(b);
		for(polyIter = this->mesh.begin(); polyIter < this->mesh.end(); polyIter++)
		{
			glBegin(glMode);
			n = polyIter->getNormal();
			glNormal3f(n->getX(), n->getY(), n->getZ());
			for(a = 0; a < 3; a++)
			{
				pidx = polyIter->getVertex(a)->pointIndex;
				p = this->points[pidx];
				glVertex3f( p.getX(), p.getY(), p.getZ());
			}
			glEnd();
		}
		// The only reason to do this loop again is if we are doing hidden surface
		// wireframe. The getGLMode function defaults to returning GL_POINTS if
		// there is no second type of drawing, so break out of the loop.
		if(this->getGLMode(1) == GL_POINTS) break;
	}
	glPopMatrix();
	glEnable(GL_LIGHTING);	// Some modes turn off lighting
  glFlush();
	return;
}

void GLObject::calcNormal(Polygon *poly)	// Calculate normal of the polygon
{
	Vector3D a, b, c;
	int va, vb, vc;
	va = poly->getVertex(0)->pointIndex;	// Index to first point in polygon
	vb = poly->getVertex(1)->pointIndex;	// Index to second point in polygon
	vc = poly->getVertex(2)->pointIndex;	// Index to third point in polygon
	a = this->points[vb] - this->points[va];
	b = this->points[vc] - this->points[vb];
	c = a / b;	// Cross product
	poly->setNormal(c);
	return;
}

void GLObject::setDrawMode(int mode)
{
	this->drawMode = mode;
	return;
}

void GLObject::spinY(int mode)
{
	this->spinMode = mode;
	return;
}

void GLObject::setSpin(void)
{
	switch(this->spinMode)
	{
		case -1:
			this->angleY = 0.0;
			this->spinMode = 0;
			break;
		case 1:
			this->angleY += 1.0;
		case 0:
			glRotatef(this->angleY, 0.0, 1.0, 0.0);
		  // Redraw the scene
		  glutPostRedisplay();
			break;
	}
	return;
}

int GLObject::getGLMode(int order)	// return the GL draw mode based on order
{
	int a = GL_POINTS;	// Default to points
	switch(this->drawMode)
	{
		case POINTS:	// From drawmodes.h
			if(order == 0)
			{
				a = GL_POINTS;
				glDisable(GL_LIGHTING);
				this->setMaterial(false);
			}
		break;
		case WIREFRAME:
			if(order == 0)
			{
				a = GL_LINES;
				glDisable(GL_LIGHTING);
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				this->setMaterial(false);
			}
		break;
		case WIREFRAME | HIDDENSURFACE:
			switch(order)
			{
				case 0:
					a = GL_POLYGON;
					glDisable(GL_LIGHTING);
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					glEnable(GL_POLYGON_OFFSET_FILL);
					glPolygonOffset(this->factor, this->units);
					cout << "Factor: " << this->factor << " Units: " << this->units << endl;
					this->setMaterial(true);
				break;
				case 1:
					a = GL_LINES;
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					this->setMaterial(false);
					glDisable(GL_POLYGON_OFFSET_FILL);
				break;
			}
		break;
		case POLYGON:
		case TEXTURE:
		case ENVIRONMENT:
		case TEXTURE | ENVIRONMENT:
			if(order == 0)
			{
				a = GL_POLYGON;
				glEnable(GL_LIGHTING);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				this->setMaterial(false);
			}
		break;
	}
	return a;
}

void GLObject::setMaterial(int hidden)
{
	if(!hidden)
	{
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glColor3f(this->fg[0], this->fg[1], this->fg[2]);
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_DIFFUSE, h_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, h_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, h_shininess);
		glMaterialfv(GL_FRONT, GL_AMBIENT, h_ambient);
		glColor3f(this->bg[0], this->bg[1], this->bg[2]);
	}
	return;
}
