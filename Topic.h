#pragma once
#include "User.h"
#include "Question.h"

class Topic
{
	MyString _title;
	const User* _author = nullptr;
	MyString _content;
	unsigned _id;
	MyVector<Question> _questions;
	Question* _currentQ = nullptr;

	int getQuestionIdx(const MyString& title) const;
	int getQuestionIdx(unsigned id) const;
public:
	Topic() = default;
	Topic(const MyString& title, const User* author, const MyString& content, unsigned id);
	void addQuestion(const User* author, const MyString& title, const MyString& content);
	bool containsText(const MyString& text) const;
	void printTopicInfo() const;
	const MyString& getTitle() const;
	unsigned getId() const;
	void printTopicData() const;
	void printQuestions() const;

	const Question& getCurrentQ(const MyString& title);
	const Question& getCurrentQ(unsigned id);
	const Question& getCurrentQ();
	void addCommentToCurrentQ(const MyString& content, const User* author);
	void addReplyToCurrentQ(unsigned id, const MyString& content, const User* author);
	void addUpvoteToCommentOnQ(unsigned id, const User* author);
	void addDownvoteToCommentOnQ(unsigned id, const User* author);
	void closePost();
};


