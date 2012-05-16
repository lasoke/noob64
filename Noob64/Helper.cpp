#include "StdAfx.h"

string format_number(string s, char c, int frequency)
{
	int length = s.length();
	string::iterator i = s.end();
	while (length - frequency > 0)
	{
		i -= frequency;
		length -= frequency;
		s.insert(i, c);
	}
	return s;
}