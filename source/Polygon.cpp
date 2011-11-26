#include "Polygon.h"

Polygon::Polygon(String face)
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
	//cout << "Polygon Destructor" << endl;	// Debug
	return;
}

void Polygon::setPolygon(String face)
{
	String p1, p2, p3;
	cout << face << endl;	// Debug
	p1 = face.split(' ');
	p2 = face.split(' ');
	p3 = face;
	cout << "p1=" << p1 << " p2=" << p2 << " p3=" << p3 << endl;
	return;
}

