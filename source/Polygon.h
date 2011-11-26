#ifndef POLYGON_H_
#define POLYGON_H_
#include <iostream>
using namespace std;
#include "String.h"

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
//	Vector3D *getNormal(void);	// Return pointer to polygon normal
	private:
		Vertex vertex[3];	// Statically contain 3 vertices for this project
//	Vector3D normal;	// Hold the polygon normal
};

#endif
