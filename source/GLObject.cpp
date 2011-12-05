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
			this->calcPolygonNormal(&tempPoly);	// Find the normal
			this->mesh.push_back(tempPoly);	// Store indices
		}
	}
	this->calcVertexNormals();
//	cout << "Number of polygons: " << this->mesh.size() << endl;
	file.close();
	this->spinMode = 0;
	this->angleY = 0.0;
	this->drawMode = POINTS;
	this->smooth = 0;
	for(int a = 0; a < 3; a++)
	{
		bg[a] = 0.5;
		fg[a] = 1.0;
	}
	return;
}

GLObject::~GLObject()
{
//	cout << "Object destructor" << endl;
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
	int pidx, a, glMode, b, tidx;
	Point p;
	TextureVertex t;
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
			if(!this->smooth)
			{
				n = polyIter->getNormal();
				glNormal3f(n->getX(), n->getY(), n->getZ());
			}
			for(a = 0; a < 3; a++)
			{
				pidx = polyIter->getVertex(a)->pointIndex;
				p = this->points[pidx];
				if(this->smooth)
				{
					n = p.getVertexNormal();
					glNormal3f(n->getX(), n->getY(), n->getZ());
				}
				if((this->drawMode == TEXTURE) || (this->drawMode == ENVIRONMENT))
				{
					tidx = polyIter->getVertex(a)->textureIndex;
					t = this->tvertex[tidx];
					glTexCoord2f(t.getU(), t.getV());
				}
				glVertex3f( p.getX(), p.getY(), p.getZ());
			}
			glEnd();
		}
		// The only reason to do this loop again is if we are doing hidden surface
		// wireframe. The getGLMode function defaults to returning GL_POINTS if
		// there is no second type of drawing, so break out of the loop.
		switch(this->drawMode)
		{
			case POINTS:
			case WIREFRAME:
			case POLYGON:
				b = 2;	// Cheesy way to break the loop
			break;
		}
	}
	glPopMatrix();
	glEnable(GL_LIGHTING);	// Some modes turn off lighting
  glFlush();
	return;
}

void GLObject::calcPolygonNormal(Polygon *poly)	// Calculate normal of polygon
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

void GLObject::calcVertexNormals(void)
{
	vector<Polygon>::iterator polyIter1;
	vector<Polygon>::iterator polyIter2;
	Point *point1;
	int pidx1;
	int pidx2;
	int a, b;
	Vector3D v;
	Vector3D *n1;
	for(polyIter1 = this->mesh.begin(); polyIter1 < this->mesh.end() - 1;
			polyIter1++)
	{
		for(a = 0; a < 3; a++)
		{
			pidx1 = polyIter1->getVertex(a)->pointIndex;	// Index to current point
			point1 = &this->points[pidx1];	// Point to current point
			if(!point1->isVertexNormalDone())
			{
				n1 = polyIter1->getNormal();
				v.set(*n1);	// Initialize with current polygon normal
				for(polyIter2 = polyIter1 + 1; polyIter2 < this->mesh.end();
						polyIter2++)
				{
					for(b = 0; b < 3; b++)
					{
						pidx2 = polyIter2->getVertex(b)->pointIndex;// Index to other point
						if(pidx1 == pidx2)	// Found point in this polygon?
						{
							n1 = polyIter2->getNormal();
							v = v + *n1;
						}
					}
				}
				v.normalize();
				point1->setVertexNormal(&v);
			}
		}
	}
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
				a = GL_LINE_LOOP;
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
					glPolygonOffset(1.0, 1.0);
					this->setMaterial(true);
				break;
				case 1:
					a = GL_LINE_LOOP;
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					this->setMaterial(false);
					glDisable(GL_POLYGON_OFFSET_FILL);
					break;
			}
		break;
		case TEXTURE:
			this->drawTexture(order);			// Set up the texture
			a = this->drawPolygons(order);
		break;
		case ENVIRONMENT:
			this->drawEnvironment(order);	// Set up the environment mapping
			a =this->drawPolygons(order);
		break;
		case TEXTURE | ENVIRONMENT:
			this->drawTexture(order);			// Set up the texture
			this->drawEnvironment(order);	// Set up the environment mapping
			a = this->drawPolygons(order);
		break;
		case POLYGON:
			a = this->drawPolygons(order);
		break;
	}
	return a;
}

void GLObject::drawTexture(int order)		// Draw with textured polygons
{
	switch(order)
	{
		case 0:
			glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, this->texName[MARBLE] );
		break;
		case 1:
			glDisable( GL_TEXTURE_2D );
		break;
	}
	return;
}

void GLObject::drawEnvironment(int order)
// Draw with environment shaded polygons
{
	switch(order)
	{
		case 0:
		  glEnable( GL_TEXTURE_GEN_S );
		  glEnable( GL_TEXTURE_GEN_T );
			glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, this->texName[ENVIRON_IMG] );
		break;
		case 1:
		  glDisable( GL_TEXTURE_GEN_S );
		  glDisable( GL_TEXTURE_GEN_T );
			glDisable( GL_TEXTURE_2D );
		break;
	}
	return;
}

int GLObject::drawPolygons(int order)		// Draw the polygons
{
	int	a = GL_POINTS;
	if(order == 0)
	{
		a = GL_POLYGON;
		glEnable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		this->setMaterial(false);
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

void GLObject::toggleSmooth(void)
{
	this->smooth = ~this->smooth;
	return;
}
