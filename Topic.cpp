#include "Topic.h"
#include <time.h>
#include <stdlib.h>

int Topic::getQuestionIdx(const MyString& title) const
{
	size_t count = _questions.size();
	for (int i = 0; i < count; i++)
	{
		if (_questions[i].getTitle() == title)
			return i;
	}
	return -1;
}
int Topic::getQuestionIdx(unsigned id) const
{
	size_t count = _questions.size();
	for (int i = 0; i < count; i++)
	{
		if (_questions[i].getId() == id)
			return i;
	}
	return -1;
}
Topic::Topic(const MyString& title, unsigned idxOfAuthor, const MyString& content, unsigned id):
	_title(title), _content(content)
{
	_id = id;
	_idxOfAuthor = idxOfAuthor;
}
void Topic::addQuestion(unsigned idxOfAuthor, const MyString& title, const MyString& content)
{
	srand(time(NULL));
	unsigned id = rand();
	_questions.push_back(Question(title, idxOfAuthor, content, id));
}
bool Topic::containsText(const MyString& text) const
{
	size_t len = _title.length();
	size_t tLen = text.length();
	int iter = 0;
	while (len >= tLen)
	{
		if (_title.substr(iter, tLen) == text)
			return true;
		iter++;
		len--;
	}
	return false;
}
void Topic::printTopicInfo() const
{
	std::cout << " >> " << _title << " {id:" << _id << "} " << std::endl;
}
const MyString& Topic::getTitle() const
{
	return _title;
}
unsigned Topic::getId() const
{
	return _id;
}
void Topic::printTopicData(const User* author) const
{
	std::cout << "Name: " << _title << std::endl;
	std::cout << "Description: " << _content << std::endl;
	std::cout << "Created by: " << author->getFName() << " " << author->getLName() << " { id:" << author->getId() << "} " << std::endl;
	std::cout << "Questions asked: " << _questions.size() << std::endl;
}
void Topic::getCurrentQ(const MyString& title, Question*& currentQ)
{
	int idx = getQuestionIdx(title);
	if (idx == -1)
		throw std::invalid_argument("No such question exists");

	currentQ = &_questions[idx];
}
void Topic::getCurrentQ(unsigned id, Question*& currentQ)
{
	int idx = getQuestionIdx(id);
	if (idx == -1)
		throw std::invalid_argument("No such question exists");

	currentQ = &_questions[idx];
}
void Topic::printQuestions() const
{
	size_t count = _questions.size();
	for (int i = 0; i < count; i++)
		_questions[i].printQuestion();
}

void Topic::writeToFile(std::ofstream& ofs) const
{
	writeStringToFile(ofs, _title);
	ofs.write((const char*)&_idxOfAuthor, sizeof(unsigned));
	writeStringToFile(ofs, _content);
	ofs.write((const char*)&_id, sizeof(unsigned));
	size_t countOfQs = _questions.size();
	ofs.write((const char*)&countOfQs, sizeof(size_t));
	for (int i = 0; i < countOfQs; i++)
		_questions[i].writeToFile(ofs);
}
void Topic::readFromFiLe(std::ifstream& ifs)
{
	_title = readStringFromFile(ifs);
	ifs.read((char*)&_idxOfAuthor, sizeof(unsigned));
	_content = readStringFromFile(ifs);
	ifs.read((char*)&_id, sizeof(unsigned));
	size_t countOfQs;
	ifs.read((char*)&countOfQs, sizeof(size_t));
	for (int i = 0; i < countOfQs; i++)
	{
		Question read;
		read.readFromFiLe(ifs);
		_questions.push_back(read);
	}
}