#pragma once
#include "Comment.h"
class Question
{
	MyString _title;
	const User* _author = nullptr;
	MyString _content;
	unsigned _id;
	MyVector<Comment> _comments;

	void getComment(Comment*& current, MyVector<Comment>& comments, unsigned id);

public:
	Question() = default;
	Question(const MyString& title, const User* author, const MyString& content, unsigned id);
	const MyString& getTitle() const;
	const MyString& getContent() const;
	unsigned getId() const;
	void addComment(const MyString& content, const User* author);
	void addReplyToComment(unsigned id, const MyString& content, const User* author);
	void printComments() const;
	void addUpVote(unsigned id, const User* author);
	void addDownVote(unsigned id, const User* author);
	void printQuestion() const;
};

