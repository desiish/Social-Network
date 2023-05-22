#include "SerializeFunctions.h"
void writeStringToFile(std::ofstream& ofs, const MyString& str)
{
	int len = str.length();
	ofs.write((const char*)&len, sizeof(int));

	ofs.write(str.c_str(), sizeof(char) * len);
}
MyString readStringFromFile(std::ifstream& ifs)
{
	int len = 0;
	ifs.read((char*)&len, sizeof(len));

	char* buff = new char[len + 1];
	ifs.read(buff, sizeof(char) * len);

	buff[len] = '\0';

	MyString toReturn(buff);

	delete[] buff;

	return toReturn;
}
