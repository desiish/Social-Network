#include "HelperFunctions.h"
bool isDigit(char s)
{
	return s <= '9' && s >= '0';
}
unsigned getDigitFromChar(char s)
{
	if (!isDigit(s))
		return 10;
	return s - '0';
}
unsigned getNumFromStr(const MyString& str)
{
	size_t len = str.length();
	unsigned mult = 1;
	unsigned res = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		res += mult * getDigitFromChar(str[i]);
		mult *= 10;
	}
	return res;
}