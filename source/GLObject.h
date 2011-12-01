#ifndef GLOBJECT_H_
#define GLOBJECT_H_
#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include "Polygon.h"
#include "TextureVertex.h"
#include "Point.h"

class GLObject
{
	public:
		GLObject(String objFile);
		virtual ~GLObject();
		void print(void);	// Debug... print the contents of the vectors
		void draw(void);
	private:
		vector <Polygon> mesh;
		vector <TextureVertex> tvertex;
		vector <Point> points;
};

#endif
