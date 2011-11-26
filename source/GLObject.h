#ifndef GLOBJECT_H_
#define GLOBJECT_H_
#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include "Polygon.h"

class GLObject
{
	public:
		GLObject(String objFile);
		virtual ~GLObject();
	private:
// Use Vector 3D for points
// Texture coordinates are 2D and are placed in a vector of 2D structure.
// Calculate normals based on vector 3D points (data belongs to polygons)
// Polygons are different objects. For this project, polygons only need to
// worry about 3 points. Polygons also need to worry about texture coordinates.
		vector <Polygon> mesh;
};

#endif
