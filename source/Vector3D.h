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
#ifndef Vector3D_H_
#define Vector3D_H_

#include <math.h>

#define PI 3.14159265359
class Vector3D
{
	public:
		Vector3D(double x = 0.0, double y = 0.0, double z = 0.0);
		void set(double x, double y, double z);
		void set(Vector3D &x);
		void get(double &x, double &y, double &z);
		double getX(void);
		double getY(void);
		double getZ(void);
		void normalize(void);
		double magnitude(void);
    friend Vector3D operator +(Vector3D &a, Vector3D &b);
    friend Vector3D operator -(Vector3D &a, Vector3D &b);
    friend double operator *(Vector3D &a, Vector3D &b);
    friend Vector3D operator /(Vector3D &a, Vector3D &b);
	private:
		double x;
		double y;
		double z;
};

double findAngle(Vector3D a, Vector3D b);

#endif
