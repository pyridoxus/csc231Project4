// Specialized version of the string class

#include "String.h"

String::String(const char *s): string(s)
{
	return;
}

String::String(void): string()
{
	return;
}

String::~String()
{
	return;
}

string String::split(const char c)
// Split the internal string on the first occurrence of the character c. Return
// the left part of the string before c. Internal string contains the right part
// of string after c. If c not found, then return empty string, and internal
// string is unchanged.
{
	string s;
	return s;
}
