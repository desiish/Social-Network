#include "User.h"
User::User(const MyString& fn, const MyString& ln, const MyString& pass, unsigned id): _firstName(fn), _lastName(ln), _pass(pass)
{
	_id = id;
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