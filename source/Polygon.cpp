#include "Polygon.h"
#include <stdlib.h>

Polygon::Polygon(String face)
{
	this->setPolygon(face);
	return;
}

Polygon::Polygon(void)
{
	return;
}

Polygon::~Polygon()
{
	//cout << "Polygon Destructor" << endl;	// Debug
	return;
}

void Polygon::setPolygon(String face)
{
	String p[4];	// 4th is just a temporary string
	int a;
//	cout << face << endl;	// Debug
	p[0] = face.split(' ');	// face holds 3 points (vertex and texture indices)
	p[1] = face.split(' ');	// now face holds 2 points
	p[2] = face;						// now face holds the last point
//	cout << "p1=" << p[0] << " p2=" << p[1] << " p3=" << p[2] << endl;	// Debug
	for(a = 0; a < 3; a++)
	{
		p[3] = p[a].split('/');	// Store the string version of point index
		this->vertex[a].pointIndex = atoi(p[3].c_str());
		this->vertex[a].textureIndex = atoi(p[a].c_str()); // Convert texture index
//		cout << "p" << a + 1 << "= " << this->vertex[a].pointIndex << "/";
//		cout << this->vertex[a].textureIndex << " ";
	}
//	cout << endl;
	return;
}

Vertex *Polygon::getVertex(unsigned int index)
// Return pointer to vertex at index
{
	return this->vertex + index;
}

void Polygon::draw(void)
{

	return;
}
