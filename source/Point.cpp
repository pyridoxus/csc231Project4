#include "Point.h"
#include <stdlib.h>

Point::Point(void): Vector3D(0.0, 0.0, 0.0)
{
	return;
}

Point::Point(String s): Vector3D(0.0, 0.0, 0.0)
{
	this->setPoint(s);
	return;
}

Point::~Point()
{
}

void Point::setPoint(String s)
{
	String t;
	double x, y, z;
	t = s.split(' ');	// t holds x, s holds y and z
	x = atof(t.c_str());
	t = s.split(' ');	// t holds y, s holds z
	y = atof(t.c_str());
	z = atof(s.c_str());
	this->set(x, y, z);
	return;
}
