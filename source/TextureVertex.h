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
#ifndef TEXTUREVERTEX_H_
#define TEXTUREVERTEX_H_
#include "String.h"

class TextureVertex
{
	public:
		TextureVertex(String s); 	// Set the u,v coordinates based on string
		TextureVertex(void);			// Set the u,v coordinates later
		virtual ~TextureVertex();
		float getU(void);
		float getV(void);
		void setUV(String s);
	private:
		float u, v;
};

#endif
