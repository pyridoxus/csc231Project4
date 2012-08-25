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
#ifndef POLYGON_H_
#define POLYGON_H_
#include <iostream>
using namespace std;
#include "String.h"
#include <GL/glut.h>
#include <GL/glext.h>
#include "Vector3D.h"

struct Vertex
{
		int pointIndex;
		int textureIndex;
};

class Polygon
{
	// There are two ways to create a Polygon object.
		// 1) Send in the face string data when allocating the polygon
		// 2) Create empty polygon and set the polygon data later using the set
		//		member function.
	public:
		Polygon(String face); // Use string from file to build polygon
		Polygon(void); 				// Create an empty polygon
		virtual ~Polygon();
		Vertex *getVertex(unsigned int index);	// Return pointer to vertex at index
		void setPolygon(String face); // Use string from file to setup the polygon
		Vector3D *getNormal(void);	// Return pointer to polygon normal
		void setNormal(Vector3D &norm);	// Set the normal (and normalize)
	private:
		Vertex vertex[3];	// Statically contain 3 vertices for this project
		Vector3D normal;	// Hold the polygon normal
};

#endif
