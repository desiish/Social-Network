#pragma once
#include "User.h"
#include "Question.h"

class Topic
{
	MyString _title;
	unsigned _idxOfAuthor;
	MyString _content;
	unsigned _id;
	MyVector<Question> _questions;

	int getQuestionIdx(const MyString& title) const;
	int getQuestionIdx(unsigned id) const;
public:
	Topic() = default;
	Topic(const MyString& title, unsigned idxOfAuthor, const MyString& content, unsigned id);
	void addQuestion(unsigned idxOfAuthor, const MyString& title, const MyString& content);
	bool containsText(const MyString& text) const;
	void printTopicInfo() const;
	const MyString& getTitle() const;
	unsigned getId() const;
	void printTopicData(const User* author) const;
	void printQuestions() const;

	void getCurrentQ(const MyString& title, Question*& currentQ);
	void getCurrentQ(unsigned id, Question*& currentQ);

	void writeToFile(std::ofstream& ofs) const;
	void readFromFiLe(std::ifstream& ifs);
};


