#include "User.h"
#include "SerializeFunctions.h"
User::User(const MyString& fn, const MyString& ln, const MyString& pass, unsigned id, unsigned idxInSystem): _firstName(fn), _lastName(ln), _pass(pass)
{
	_id = id;
	_idxInSystem = idxInSystem;
}
void User::setPoints(unsigned points)
{
	_pts = points;
}
unsigned User::getPoints() const
{
	return _pts;
}
bool User::isPass(const MyString& pass) const
{
	return pass == _pass;
}
bool User::isName(const MyString& name) const
{
	return name == _firstName;
}
void User::printUserInfo() const
{
	std::cout << _firstName << " " << _lastName << ", having " << _pts << " points." << std::endl;
}
const MyString& User::getFName() const
{
	return _firstName;
}
const MyString& User::getLName() const
{
	return _lastName;
}
unsigned User::getId() const
{
	return _id;
}
unsigned User::getIdxInSystem() const
{
	return _idxInSystem;
}
void User::writeToFile(std::ofstream& ofs) const
{
	writeStringToFile(ofs, _firstName);
	writeStringToFile(ofs, _lastName);
	writeStringToFile(ofs, _pass);
	ofs.write((const char*)&_id, sizeof(unsigned));
	ofs.write((const char*)&_pts, sizeof(unsigned));
	ofs.write((const char*)&_idxInSystem, sizeof(unsigned));
}
void User::readFromFiLe(std::ifstream& ifs)
{
	_firstName = readStringFromFile(ifs);
	_lastName = readStringFromFile(ifs);
	_pass = readStringFromFile(ifs);
	ifs.read((char*)&_id, sizeof(unsigned));
	ifs.read((char*)&_pts, sizeof(unsigned));
	ifs.read((char*)&_idxInSystem, sizeof(unsigned));
}