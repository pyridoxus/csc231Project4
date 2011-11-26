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
