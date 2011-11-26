#include "TextureVertex.h"
#include <iostream>
using namespace std;
#include <stdlib.h>

TextureVertex::TextureVertex(String s)
{
	this->setUV(s);
	return;
}

TextureVertex::TextureVertex(void)
{
	this->u = this->v = 0.0;
	return;
}

TextureVertex::~TextureVertex()
{
//	cout << "TextureVertex destructor" << endl;	// Debug
	return;
}

void TextureVertex::setUV(String s)
{
	String u;
//	cout << s << endl;	// Debug
	u = s.split(' ');
	this->u = atof(u.c_str());
	this->v = atof(s.c_str());	// After split, s contains the v coordinate
//	cout << "u=" << this->u << " v=" << this->v << endl;	// Debug
	return;
}

float TextureVertex::getU(void)
{
	return this->u;
}

float TextureVertex::getV(void)
{
	return this->v;
}
