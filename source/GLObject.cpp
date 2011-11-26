#include "GLObject.h"

GLObject::GLObject(string objFile)
{
	char s[256];
	fstream file(objFile.c_str(), fstream::in);
	while(file.good())
	{
		file.getline(s, 256);
		cout << s << endl;
	}
	file.close();
	return;
}

GLObject::~GLObject()
{
}

