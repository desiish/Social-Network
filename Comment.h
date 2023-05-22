#pragma once
#include "User.h"
#include "MyVector.hpp"
#include "SerializeFunctions.h"
class Comment
{
	unsigned _indexOfAuthor = 0;
	MyString _content;
	unsigned _id;
	MyVector<Comment> _replies;
	MyVector<unsigned> _upvotes;
	MyVector<unsigned> _downvotes;

public:
	Comment() = default;
	Comment(unsigned idxOfAuthor, const MyString& content, unsigned id);
	unsigned getId() const;
	void printCommentInfo(size_t countOfSpaces) const;
	void addReply(const MyString& content, unsigned idxOfAuthor);
	void addOrRemoveUpVote(unsigned idxOfAuthor);
	void addOrRemoveDownVote(unsigned idxOfAuthor);
	MyVector<Comment>& getReplies();

	void writeToFile(std::ofstream& ofs) const;
	void readFromFiLe(std::ifstream& ifs);
};

