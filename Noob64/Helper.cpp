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

word getWord(char **ptr)
{
	word value = 0;
	char ch = **ptr;

    while (ch == ' ' || ch == '\t' || ch == '\n')
        ch = *(++*ptr);

    for (int i = 0; i < 8; i++)
	{
        if (ch >= '0' && ch <= '9')
            value = (value << 4) + (ch - '0');
        else if (ch >= 'A' && ch <= 'F')
            value = (value << 4) + (ch - 'A' + 10);
        else if (ch >= 'a' && ch <= 'f')
            value = (value << 4) + (ch - 'a' + 10);
        else
            return value;
        ch = *(++*ptr);
    }
	return value;
}