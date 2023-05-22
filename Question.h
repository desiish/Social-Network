#pragma once
#include "Comment.h"
class Question
{
	MyString _title;
	unsigned _idxOfAuthor;
	MyString _content;
	unsigned _id;
	MyVector<Comment> _comments;

	void getComment(Comment*& current, MyVector<Comment>& comments, unsigned id);

public:
	Question() = default;
	Question(const MyString& title, unsigned idxOfAuthor, const MyString& content, unsigned id);
	const MyString& getTitle() const;
	const MyString& getContent() const;
	unsigned getId() const;
	void addComment(const MyString& content, unsigned idxOfAuthor);
	void addReplyToComment(unsigned id, const MyString& content, unsigned idxOfAuthor);
	void printComments() const;
	void addUpVote(unsigned id, unsigned idxOfAuthor);
	void addDownVote(unsigned id, unsigned idxOfAuthor);
	void printQuestion() const;

	void writeToFile(std::ofstream& ofs) const;
	void readFromFiLe(std::ifstream& ifs);
};

