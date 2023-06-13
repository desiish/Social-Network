#pragma once
#include "MyString.h"
class User
{
	MyString _firstName = "Unknown";
	MyString _lastName = "Unknown";
	MyString _pass = "N/A";
	unsigned _id = 0;
	unsigned _pts = 0;
	unsigned _idxInSystem = 0;

public:

	User() = default;
	User(const MyString& fn, const MyString& ln, const MyString& pass, unsigned id, unsigned idxInSystem);
	void setPoints(unsigned points);
	unsigned getPoints() const;
	bool isPass(const MyString& pass) const;
	bool isName(const MyString& name) const;
	void printUserInfo() const;
	const MyString& getFName() const;
	const MyString& getLName() const;
	unsigned getId() const;
	unsigned getIdxInSystem() const;

	void writeToFile(std::ofstream& ofs) const;
	void readFromFiLe(std::ifstream& ifs);
};
