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
		void toggleSmooth(void);
	private:
		vector <Polygon> mesh;
		vector <TextureVertex> tvertex;
		vector <Point> points;
		int drawMode;
		int spinMode;
		float angleY;
		float bg[3];
		float fg[3];
		int smooth;
		void calcPolygonNormal(Polygon *poly);	// Calculate the normal of polygon
		void calcVertexNormals(void);	// Calculate the normal of vertices
		void setSpin(void);	// Set angle of spin (or reset) based on state
		int getGLMode(int order);	// return the GL draw mode based on order
		void setMaterial(int hidden);		// set the material for GL
};


#endif
