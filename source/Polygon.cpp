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
		this->vertex[a].pointIndex = atoi(p[3].c_str()) - 1;
		this->vertex[a].textureIndex = atoi(p[a].c_str()) - 1;
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

Vector3D *Polygon::getNormal(void)
{
	return &this->normal;
}

void Polygon::setNormal(Vector3D &norm)	// Set the normal (and normalize)
{
	this->normal.set(norm);
	this->normal.normalize();
	return;
}
