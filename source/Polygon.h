#ifndef POLYGON_H_
#define POLYGON_H_
#include <iostream>
using namespace std;

struct Vertex
{
		int pointIndex;
		int textureIndex;
};

class Polygon
{
	public:
		Polygon(char *face); // Use string from file to build polygon
		virtual ~Polygon();
		Vertex *getVertex(unsigned int index);	// Return pointer to vertex at index
//	Vector3D *getNormal(void);	// Return pointer to polygon normal
	private:
		Vertex vertex[3];	// Statically contain 3 vertices for this project
//	Vector3D normal;	// Hold the polygon normal
};

#endif
