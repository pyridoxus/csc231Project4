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

// Image data
#define MARBLE	 			0
#define ENVIRON_IMG	 	1
#define NUM_TEXTURES	2

class GLObject
{
	public:
		GLObject(String objFile);
		virtual ~GLObject();
		void print(void);	// Debug... print the contents of the vectors
		void setDrawMode(int mode);
		void setSpin(int spin);	// Set angle of spin (or reset) based on state
		void toggleSmooth(void);
		void draw(void);
		GLuint texName[ NUM_TEXTURES ];
	private:
		vector <Polygon> mesh;
		vector <TextureVertex> tvertex;
		vector <Point> points;
		int drawMode;
		float angleY;
		float bg[3];
		float fg[3];
		int smooth;
		void glDraw(int glMode);
		void calcPolygonNormal(Polygon *poly);	// Calculate the normal of polygon
		void calcVertexNormals(void);	// Calculate the normal of vertices
		void setMaterial(int hidden);		// set the material for GL
		void drawTexture(void);		// Draw with textured polygons
		void drawEnvironment(void);	// Draw with environment shaded polygons
		void drawTextureEnvironment(void);		// Draw with textured polygons
		void drawPolygons(void);		// Draw the polygons
		void drawPoints(void);		// Draw the points
		void drawWireframe(void);		// Draw in wireframe
		void drawHiddenWireframe(void);		// Draw in hidden surface wireframe
};


#endif
