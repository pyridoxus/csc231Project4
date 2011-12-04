#ifndef GLOBJECT_H_
#define GLOBJECT_H_
#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include "Polygon.h"
#include "TextureVertex.h"
#include "Point.h"
#include "drawModes.h"

class GLObject
{
	public:
		GLObject(String objFile);
		virtual ~GLObject();
		void print(void);	// Debug... print the contents of the vectors
		void draw(void);
		void setDrawMode(int mode);
		void spinY(int mode);
	private:
		vector <Polygon> mesh;
		vector <TextureVertex> tvertex;
		vector <Point> points;
		int drawMode;
		int spinMode;
		float angleY;
		void calcNormal(Polygon *poly);	// Calculate the normal of the polygon
		void setSpin(void);	// Set angle of spin (or reset) based on state
		int getGLMode(int order);	// return the GL draw mode based on order
};

#endif
