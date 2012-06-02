#pragma once

string format_number(string s, char c, int frequency);

word getWord(char **ptr);

template <typename Type>
inline sdword sign_extended(Type data)
{
	data = (sdword) ((Type) data);
	return data;
};