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
#include "Vector3D.h"

Vector3D::Vector3D(double x, double y, double z)
{
	this->set(x, y, z);
	return;
}

void Vector3D::set(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	return;
}

void Vector3D::get(double &x, double &y, double &z)
{
	x = this->x;
	y = this->y;
	z = this->z;
	return;
}

double Vector3D::getX(void)
{
	return this->x;
}

double Vector3D::getY(void)
{
	return this->y;
}

double Vector3D::getZ(void)
{
	return this->z;
}

Vector3D operator +(Vector3D &a, Vector3D &b)
{
	return Vector3D(a.getX() + b.getX(),
								a.getY() + b.getY(),
								a.getZ() + b.getZ());
}

Vector3D operator -(Vector3D &a, Vector3D &b)
{
	return Vector3D(a.getX() - b.getX(),
								a.getY() - b.getY(),
								a.getZ() - b.getZ());
}

double operator *(Vector3D &a, Vector3D &b)
{
	return (double)( a.getX() * b.getX() +
									a.getY() * b.getY() +
									a.getZ() * b.getZ());
}

Vector3D operator /(Vector3D &a, Vector3D &b)
{
	return Vector3D(a.getY() * b.getZ() - a.getZ() * b.getY(),
								a.getZ() * b.getX() - a.getX() * b.getZ(),
								a.getX() * b.getY() - a.getY() * b.getX());
}

void Vector3D::normalize(void)
{
	double len;
	len = this->magnitude();
	this->x /= len;
	this->y /= len;
	this->z /= len;
	return;
}

void Vector3D::set(Vector3D &x)
{
	this->x = x.getX();
	this->y = x.getY();
	this->z = x.getZ();
	return;
}

double Vector3D::magnitude(void)
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

double findAngle(Vector3D a, Vector3D b)
{
	double angle;
	angle = 180.0 * acos((a * b) / (a.magnitude() * b.magnitude())) / PI;
	return angle;
}

