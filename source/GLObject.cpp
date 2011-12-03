#include "GLObject.h"

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
	int pidx, a;
	Point p;
	Vector3D *n;
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	this->setSpin();
  for(polyIter = this->mesh.begin(); polyIter < this->mesh.end(); polyIter++)
  {
//  	cout << "Polygon:" << endl;
  	glBegin(this->drawMode);
  	n = polyIter->getNormal();
  	glNormal3f(n->getX(), n->getY(), n->getZ());
  	for(a = 0; a < 3; a++)
  	{
  		pidx = polyIter->getVertex(a)->pointIndex;
  		p = this->points[pidx];
//  		cout << "(" << p.getX() << ", " << p.getY() << ", " << p.getZ() << ")" << endl;
  		glVertex3f( p.getX(), p.getY(), p.getZ());
  	}
  	glEnd();
  	glFlush();
  }
	glPopMatrix();
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
