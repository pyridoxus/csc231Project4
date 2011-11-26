#include "Polygon.h"

Polygon::Polygon(string face)
{
	this->setPolygon(face);
	return;
}

Polygon::Polygon(void)
{
	return;
}

Polygon::~Polygon()
{
	cout << "Polygon Destructor" << endl;
}

void Polygon::setPolygon(string face)
{
	cout << face << endl;
	return;
}

