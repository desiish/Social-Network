#pragma once
#include "User.h"
#include "MyVector.hpp"
class Comment
{
	const User* _author = nullptr;
	MyString _content;
	unsigned _id;
	MyVector<Comment> _replies;
	MyVector<const User*> _upvotes;
	MyVector<const User*> _downvotes;

public:
	Comment() = default;
	Comment(const User* author, const MyString& content, unsigned id);
	unsigned getId() const;
	void printCommentInfo(size_t countOfSpaces) const;
	void addReply(const MyString& content, const User* author);
	void addOrRemoveUpVote(const User* author);
	void addOrRemoveDownVote(const User* author);
	MyVector<Comment>& getReplies();

};

