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
Topic::Topic(const MyString& title, const User* author, const MyString& content, unsigned id):
	_title(title), _content(content)
{
	_id = id;
	_author = author;
}
void Topic::addQuestion(const User* author, const MyString& title, const MyString& content)
{
	srand(time(NULL));
	unsigned id = rand();
	_questions.push_back(Question(title, author, content, id));
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
void Topic::printTopicData() const
{
	std::cout << "Name: " << _title << std::endl;
	std::cout << "Description: " << _content << std::endl;
	std::cout << "Created by: " << _author->getFName() << " " << _author->getLName() << " { id:" << _author->getId() << "} " << std::endl;
	std::cout << "Questions asked: " << _questions.size() << std::endl;
}
const Question& Topic::getCurrentQ(const MyString& title) 
{
	int idx = getQuestionIdx(title);
	if (idx == -1)
		throw std::invalid_argument("No such question exists");

	std::cout << "Index: " << idx << std::endl;
	_currentQ = &_questions[idx];
	return *_currentQ;
}
const Question& Topic::getCurrentQ(unsigned id) 
{
	int idx = getQuestionIdx(id);
	if (idx == -1)
		throw std::invalid_argument("No such question exists");
	std::cout << "Index: " << idx<<std::endl;
	_currentQ = &_questions[idx];
	return *_currentQ;
}
const Question& Topic::getCurrentQ()
{
	return *_currentQ;
}
void Topic::addCommentToCurrentQ(const MyString& content, const User* author)
{
	if (_currentQ == nullptr)
		throw "No question chosen!";

	_currentQ->addComment(content, author);
}
void Topic::addReplyToCurrentQ(unsigned id, const MyString& content, const User* author)
{
	if (_currentQ == nullptr)
		throw "No question chosen!";

	std::cout << id << " " << content << std::endl;
	_currentQ->addReplyToComment(id, content, author);
}
void Topic::addUpvoteToCommentOnQ(unsigned id, const User* author)
{
	_currentQ->addUpVote(id, author);
}
void Topic::addDownvoteToCommentOnQ(unsigned id, const User* author)
{
	_currentQ->addDownVote(id, author);
}
void Topic::closePost()
{
	_currentQ = nullptr;
}
void Topic::printQuestions() const
{
	size_t count = _questions.size();
	for (int i = 0; i < count; i++)
		_questions[i].printQuestion();
}