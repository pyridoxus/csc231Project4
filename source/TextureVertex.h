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
