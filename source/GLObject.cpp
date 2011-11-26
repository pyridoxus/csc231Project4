#include "GLObject.h"

GLObject::GLObject(String objFile)
{
	char s[256];
	String st, dataType;
	Polygon tempPoly;
	TextureVertex tempTVertex;
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
			tempTVertex.setUV(st);	// Process string into floats
			this->tvertex.push_back(tempTVertex);	// Store the floats
		}
		else if(!dataType.compare("f"))
		{
			tempPoly.setPolygon(st);	// Process string into indices (vertex/texture)
			this->mesh.push_back(tempPoly);	// Store indices
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

void GLObject::print(void)
{
  vector<TextureVertex>::iterator tviter;
  vector<Polygon>::iterator piter;
  int a;

  for(tviter = this->tvertex.begin(); tviter < this->tvertex.end(); tviter++)
  {
  	cout << "(" << tviter->getU() << ", " << tviter->getV() << ")" << endl;
  }
  for(piter = this->mesh.begin(); piter < this->mesh.end(); piter++)
  {
  	for(a = 0; a < 3; a++)
  	{
  		cout << piter->getVertex(a)->pointIndex << "/";
  		cout << piter->getVertex(a)->textureIndex;
  		if(a < 2) cout << ", ";
  		else cout << endl;
  	}
  }


}
