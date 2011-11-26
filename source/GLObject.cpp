#include "GLObject.h"

GLObject::GLObject(char *objFile)
{
	char s[256];
	fstream file(objFile, fstream::in);
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

