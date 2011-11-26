#include "GLObject.h"

GLObject::GLObject(String objFile)
{
	char s[256];
	String st, dataType;
	Polygon *tempPoly;
	TextureVertex *tempTVertex;
	fstream file(objFile.c_str(), fstream::in);
	while(file.good())
	{
		file.getline(s, 256);	// Get line
		st.assign(s);
		dataType = st.split(' ');
		if(!dataType.compare("v"))
		{
			// Send remainder of the string to the vertex handler
			cout << "Found vertex: " << st << endl;
		}
		else if(!dataType.compare("vt"))
		{
			// Send remainder of the string to the texture vertex handler
//			cout << "Found texture coordinates: " << st << endl;	// Debug
			tempTVertex = new TextureVertex(st);
			this->tvertex.push_back(*tempTVertex);
		}
		else if(!dataType.compare("f"))
		{
			tempPoly = new Polygon(st);
			this->mesh.push_back(*tempPoly);
		}
	}
	cout << "Number of polygons: " << this->mesh.size() << endl;
	file.close();
	return;
}

GLObject::~GLObject()
{
	cout << "Object destructor" << endl;
	this->mesh.clear();	// Calls the mesh destructors.
	this->tvertex.clear();	// Calls the tvertex destructors.
	return;
}

