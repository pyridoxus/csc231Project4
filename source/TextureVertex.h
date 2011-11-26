#ifndef TEXTUREVERTEX_H_
#define TEXTUREVERTEX_H_
#include "String.h"

class TextureVertex
{
	public:
		TextureVertex(String s); 	// Set the u,v coordinates based on string
		virtual ~TextureVertex();
		float getU(void);
		float getV(void);
	private:
		float u, v;
};

#endif
