#include "TextureVertex.h"
#include <iostream>
using namespace std;
#include <stdlib.h>

TextureVertex::TextureVertex(String s)
{
	String u;
	cout << s << endl;	// Debug
	u = s.split(' ');
	this->u = atof(u.c_str());
	this->v = atof(s.c_str());	// After split, s contains the v coordinate
	cout << "u=" << this->u << " v=" << this->v << endl;	// Debug
	return;
}

TextureVertex::~TextureVertex()
{
	cout << "TextureVertex destructor" << endl;	// Debug
	return;
}

