#include "Comment.h"
Comment::Comment(const User* author, const MyString& content, unsigned id): _content(content)
{
	_author = author;
	_id = id;
}
unsigned Comment::getId() const
{
	return _id;
}
MyVector<Comment>& Comment::getReplies()
{
	return _replies;
}
void Comment::printCommentInfo(size_t countOfSpaces) const
{
	for (int i = 0; i < countOfSpaces; i++)
		std::cout << " ";
	std::cout << ">>" << _content << " {id:" << _id << "} ";
	if (!_upvotes.empty())
		std::cout << " {upvotes: " << _upvotes.size() << "; downvotes: " << _downvotes.size() << "} ";
	std::cout << std::endl;
	if (!_replies.empty())
	{
		size_t count = _replies.size();
		for (int i = 0; i < count; i++)
			_replies[i].printCommentInfo(countOfSpaces + 2);
	}
}
void Comment::addReply(const MyString& content, const User* author)
{
	srand(time(NULL));
	unsigned id = rand();
	_replies.push_back(Comment(author, content, id));
}
void Comment::addOrRemoveUpVote(const User* author)
{
	size_t count = _upvotes.size();
	for (int i = 0; i < count; i++)
	{
		if (author == _upvotes[i])
		{
			_upvotes.erase(i);
			return;
		}
	}
	size_t other_count = _downvotes.size();
	for (int i = 0; i < other_count; i++)
	{
		if (author == _downvotes[i])
			_downvotes.erase(i);
	}
	_upvotes.push_back(author);
}
void Comment::addOrRemoveDownVote(const User* author)
{
	size_t count = _downvotes.size();
	for (int i = 0; i < count; i++)
	{
		if (author == _downvotes[i])
		{
			_downvotes.erase(i);
			return;
		}
	}
	size_t other_count = _upvotes.size();
	for (int i = 0; i < other_count; i++)
	{
		if (author == _upvotes[i])
			_upvotes.erase(i);
	}
	_downvotes.push_back(author);
}