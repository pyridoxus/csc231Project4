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
#ifndef POINT_H_
#define POINT_H_

#include "Vector3D.h"
#include "String.h"

class Point: public Vector3D
{
	public:
		Point(void);
		Point(String s);
		virtual ~Point();
		void setPoint(String s);	// Convert string from file into floats
		void setVertexNormal(Vector3D *v);		// Set the vertex normal at this point
		Vector3D *getVertexNormal(void);			// Return pointer to vertex normal
		int isVertexNormalDone(void);					// Return non-zero if calculated
	private:
		Vector3D vertexNormal;
		int calcVertexNormal;
};

#endif
