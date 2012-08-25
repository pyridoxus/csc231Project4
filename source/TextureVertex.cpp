//This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
