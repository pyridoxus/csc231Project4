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
#include "Point.h"
#include <stdlib.h>

Point::Point(void): Vector3D(0.0, 0.0, 0.0)
{
	this->vertexNormal.set(0.0, 0.0, 0.0);
	this->calcVertexNormal = 0;
	return;
}

Point::Point(String s): Vector3D(0.0, 0.0, 0.0)
{
	this->setPoint(s);
	return;
}

Point::~Point()
{
}

void Point::setPoint(String s)
{
	String t;
	double x, y, z;
	t = s.split(' ');	// t holds x, s holds y and z
	x = atof(t.c_str());
	t = s.split(' ');	// t holds y, s holds z
	y = atof(t.c_str());
	z = atof(s.c_str());
	this->set(x, y, z);
	this->vertexNormal.set(0.0, 0.0, 0.0);
	this->calcVertexNormal = 0;
	return;
}

void Point::setVertexNormal(Vector3D *v)	// Set the vertex normal at this point
{
	this->vertexNormal.set(*v);
	this->calcVertexNormal = -1;
	return;
}

Vector3D *Point::getVertexNormal(void)		// Return pointer to vertex normal
{
	return &this->vertexNormal;
}

int Point::isVertexNormalDone(void)					// Return non-zero if calculated
{
	return this->calcVertexNormal;
}
