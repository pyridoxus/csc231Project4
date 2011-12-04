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
		void getVertexNormal(Vector3D *v);		// Return pointer to vertex normal
	private:
		Vector3D vertexNormal;
};

#endif
