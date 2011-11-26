#include "GLObject.h"

GLObject::GLObject(string objFile)
{
	char s[256];
	string st;
	Polygon *tempPoly;
	fstream file(objFile.c_str(), fstream::in);
	while(file.good())
	{
		file.getline(s, 256, ' ');	// Parse through file
		st.assign(s);
		if(!st.compare("v"))
		{
			file.getline(s, 256);
			st.assign(s);
			// Send remainder of the string to the vertex handler
			cout << "Found vertex" << endl;
		}
		if(!st.compare("vt"))
		{
			file.getline(s, 256);
			st.assign(s);
			// Send remainder of the string to the texture coordinate handler
			cout << "Found texture coordinates" << endl;
		}
		if(!st.compare("f"))
		{
			file.getline(s, 256);
			st.assign(s);
			tempPoly = new Polygon(st);
			this->mesh.push_back(tempPoly);
		}
	}
	file.close();
	return;
}

GLObject::~GLObject()
{
}

