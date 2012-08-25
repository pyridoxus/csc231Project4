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
#ifndef STRING_H_
#define STRING_H_
#include <iostream>
using namespace std;

class String: public string
{
	public:
		String(const char *s);
		String(void);
		String(string s);
		String split(const char c);	// Split the internal string on the first
																// occurrence of the character c. Return the
																// left part of the string before c. Internal
																// string contains the right part of string
																// after c. If c not found, then return empty
																// string, and internal string is unchanged.
		virtual ~String();
};

#endif /* STRING_H_ */
